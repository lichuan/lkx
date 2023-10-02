#include <stdlib.h>
#include "lkx/parse.h"

bool parse_hub_file(lkx_Hub *hub, FILE *fp)
{
  uint32 line_num = 1;
  char *file = hub->hub_path;
  int32 c;
  bool end_is_valid = false;
  const char *import_path_head1 = "[string]";
  const char *import_path_head2 = "_lkx_import_path_";
  bool comment_1st = false;
  bool comment_2nd = false;
  bool parse_comment = true;
  bool import_path_end = false;
  bool path_string_start = false;
  bool path_string_end = false;
  int32 string_end_num = 0;
  bool string_end_comma = true;
  int32 comma_num = 0;
  int32 line_no_comma = 0;
  bool path_string_empty = true;
  bool comment_is_valid = true;
  bool space_is_valid = true;
  bool newline_is_valid = true;
  int32 idx = 0;
  int32 row = 0;
  int32 col = 0;
  lkx_Rbuf *rbuf = calloc(1, sizeof(lkx_Rbuf));

  while(true)
  {
    if(rbuf->idx == rbuf->size)
    {
      if(rbuf->size > 0 && rbuf->size < READ_SZ)
      {
        return end_is_valid;
      }

      rbuf->size = fread(rbuf->buf, 1, READ_SZ, fp);
      rbuf->idx = 0;
      printf("Read buf size: %d from hub file\n", rbuf->size);

      if(rbuf->size < READ_SZ)
      {
        if(ferror(fp) != 0)
        {
          printf("Error happened when parse hub file! file: %s, line: %d\n", file, line_num);
          return false;
        }

        if(rbuf->size == 0)
        {
          return end_is_valid;
        }
      }
    }

    c = rbuf->buf[rbuf->idx++];

    if(parse_comment)
    {
      if(comment_2nd)
      {
        if(c != '\n') continue;
      }
      else if(comment_1st)
      {
        if(c != '/')
        {
          printf("Comment format is invalid! file: %s, line: %d\n", file, line_num);
          return false;
        }

        if(!comment_is_valid)
        {
          printf("Comment format is invalid! file: %s, line: %d\n", file, line_num);
          return false;
        }

        comment_2nd = true;
        continue;
      }
      else if(c == '/')
      {
        comment_1st = true;
        continue;
      }
    }

    if(c == '\t')
    {
      printf("Tab is not allowed here! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == '\r')
    {
      printf("CR is not allowed here! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == ';')
    {
      printf("Semicolon is not allowed here! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == ' ')
    {
      if(!space_is_valid)
      {
        printf("Space is not allowed here! file: %s, line: %d\n", file, line_num);
        return false;
      }

      if(path_string_end)
      {
        string_end_comma = false;
      }

      continue;
    }

    if(c == '\n')
    {
      if(!newline_is_valid)
      {
        printf("LF is not allowed here! file: %s, line: %d\n", file, line_num);
        return false;
      }

      ++line_num;
      comment_1st = false;
      comment_2nd = false;

      if(import_path_end)
      {
        comment_is_valid = true;
        break;
      }

      if(path_string_end)
      {
        string_end_comma = false;
      }

      if(comma_num != string_end_num)
      {
        ++line_no_comma;
      }

      continue;
    }

    if(idx < 8)
    {
      if(c != import_path_head1[idx++])
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
        return false;
      }

      if(idx == 1)
      {
        space_is_valid = false;
        newline_is_valid = false;
        comment_is_valid = false;
      }

      if(idx == 8) space_is_valid = true;
      continue;
    }

    if(idx < 25)
    {
      if(c != import_path_head2[idx++ - 8])
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
        return false;
      }

      if(idx == 9) space_is_valid = false;
      if(idx == 25) space_is_valid = true;
      continue;
    }

    if(idx == 25)
    {
      if(c != '=')
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
        return false;
      }

      newline_is_valid = true;
      ++idx;
      continue;
    }

    if(idx == 26)
    {
      if(c != '[')
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
        return false;
      }

      ++idx;
      continue;
    }

    if(import_path_end)
    {
      printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == ']')
    {
      if(string_end_num == comma_num && comma_num != 0)
      {
        printf("The comma cannot appear at the end of array! file: %s, line: %d\n", file, line_num);
        return false;
      }

      import_path_end = true;
      continue;
    }

    if(c == '"')
    {
      if(path_string_end)
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num - line_no_comma);
        return false;
      }

      if(!path_string_start)
      {
        newline_is_valid = false;
        space_is_valid = false;
        path_string_start = true;
        parse_comment = false;

        if(++row > 32)
        {
          printf("The number of import path cannot exceed 32! file: %s, line: %d\n", file, line_num);
          return false;
        }

        continue;
      }

      if(path_string_empty)
      {
        printf("Import path string cannot be empty! file: %s, line: %d\n", file, line_num);
        return false;
      }

      path_string_end = true;
      string_end_comma = true;
      ++string_end_num;
      space_is_valid = true;
      newline_is_valid = true;
      continue;
    }

    if(!path_string_start)
    {
      printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(path_string_end)
    {
      if(string_end_comma)
      {
        if(c != ',')
        {
          printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
          return false;
        }

        path_string_start = false;
        path_string_end = false;
        parse_comment = true;
        path_string_empty = true;
        ++comma_num;
        col = 0;
      }
      else
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num - line_no_comma);
        return false;
      }

      continue;
    }

    path_string_empty = false;
    hub->import_path[row - 1][col] = c;

    if(++col > 127)
    {
      printf("The length of import path cannot exceed 127 bytes! file: %s, line: %d\n", file, line_num);
      return false;
    }
  }

  printf("Import path (%d):\n", row);

  for(int32 i = 0; i < row; ++i)
  {
    printf("%s\n", hub->import_path[i]);
  }

  int32 ret = parse_struct_decl(hub, fp, rbuf, hub->hub_path, line_num);

  if(ret == 0)
  {
    return false;
  }

  if(ret == -1)
  {
    return true;
  }



  return true;
}

int32 parse_struct_decl(lkx_Hub *hub, FILE *fp, lkx_Rbuf *rbuf, char *modname, int32 line_num)
{
  int32 c;
  bool end_is_valid = false;
  bool comment_1st = false;
  bool comment_2nd = false;
  bool parse_comment = true;
  const char *import_decl = "import";
  bool path_string_start = false;
  bool path_string_end = false;
  bool comment_is_valid = true;
  bool space_is_valid = true;
  bool newline_is_valid = true;
  int32 idx = 0;

  while(true)
  {
    if(rbuf->idx == rbuf->size)
    {
      if(rbuf->size > 0 && rbuf->size < READ_SZ)
      {
        if(end_is_valid)
        {
          return -1;
        }

        return 0;
      }

      rbuf->size = fread(rbuf->buf, 1, READ_SZ, fp);
      rbuf->idx = 0;
      printf("Read buf size: %d from file: %s\n", rbuf->size, modname);

      if(rbuf->size < READ_SZ)
      {
        if(ferror(fp) != 0)
        {
          printf("Error happened when parse struct! file: %s, line: %d\n", modname, line_num);
          return false;
        }

        if(rbuf->size == 0)
        {
          if(end_is_valid)
          {
            return -1;
          }

          return 0;
        }
      }
    }

    c = rbuf->buf[rbuf->idx++];

    if(parse_comment)
    {
      if(comment_2nd)
      {
        if(c != '\n') continue;
      }
      else if(comment_1st)
      {
        if(c != '/')
        {
          printf("Comment format is invalid! file: %s, line: %d\n", modname, line_num);
          return false;
        }

        if(!comment_is_valid)
        {
          printf("Comment format is invalid! file: %s, line: %d\n", modname, line_num);
          return false;
        }

        comment_2nd = true;
        continue;
      }
      else if(c == '/')
      {
        comment_1st = true;
        continue;
      }
    }

    if(c == '\t')
    {
      printf("Tab is not allowed here! file: %s, line: %d\n", modname, line_num);
      return false;
    }

    if(c == '\r')
    {
      printf("CR is not allowed here! file: %s, line: %d\n", modname, line_num);
      return false;
    }

    if(c == ';')
    {
      printf("Semicolon is not allowed here! file: %s, line: %d\n", modname, line_num);
      return false;
    }

    if(c == ' ')
    {
      if(!space_is_valid)
      {
        printf("Space is not allowed here! file: %s, line: %d\n", modname, line_num);
        return false;
      }

      continue;
    }

    if(c == '\n')
    {
      if(!newline_is_valid)
      {
        printf("LF is not allowed here! file: %s, line: %d\n", modname, line_num);
        return false;
      }

      ++line_num;
      comment_1st = false;
      comment_2nd = false;
      continue;
    }
  }

  return 1;
}

