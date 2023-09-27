#include "lkx/parse.h"

bool parse_hub_file(lkx_Hub *hub, FILE *fp)
{
  uint32 line_num = 1;
  char *file = hub->hub_path;
  int c;
  bool end_is_valid = false;
  const char *import_path_head1 = "[string]";
  const char *import_path_head2 = "_lkx_import_path_";
  bool comment_1st = false;
  bool comment_2nd = false;
  bool parse_comment = true;
  bool import_path_end = false;
  bool path_string_start = false;
  bool path_string_end = false;
  bool path_string_empty = true;
  bool comment_is_valid = true;
  bool space_is_valid = true;
  bool newline_is_valid = true;
  int idx = 0;
  char path_arr[32][128] = {0};
  int row = 0;
  int col = 0;

  while(true)
  {
    c = fgetc(fp);

    if(c == EOF)
    {
      if(ferror(fp) != 0)
      {
        printf("Error happened when parse hub file! file: %s, line: %d\n", file, line_num);
        return false;
      }

      return end_is_valid;
    }

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

        comment_2nd = true;
        continue;
      }
      else if(c == '/')
      {
        if(!comment_is_valid)
        {
          printf("Comment is not allowed here! file: %s, line: %d\n", file, line_num);
          return false;
        }

        comment_1st = true;
        continue;
      }
    }

    if(c == '\t')
    {
      printf("Tab is not allowed in lkx script! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == '\r')
    {
      printf("CR is not allowed in lkx script! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == ';')
    {
      printf("Semicolon is not allowed in lkx script! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(c == ' ')
    {
      if(!space_is_valid)
      {
        printf("Space is not allowed here! file: %s, line: %d\n", file, line_num);
        return false;
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
      import_path_end = true;
      continue;
    }

    if(c == '"')
    {
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
      continue;
    }

    if(!path_string_start)
    {
      printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
      return false;
    }

    if(path_string_end)
    {
      if(c != ',')
      {
        printf("Parse import_path failed! file: %s, line: %d\n", file, line_num);
        return false;
      }

      space_is_valid = true;
      newline_is_valid = true;
      path_string_start = false;
      path_string_end = false;
      parse_comment = true;
      col = 0;
      continue;
    }
    
    path_string_empty = false;
    path_arr[row - 1][col] = c;

    if(++col > 128)
    {
      printf("The length of import path cannot exceed 128 bytes! file: %s, line: %d\n", file, line_num);
      return false;
    }
  }

  printf("Import path:\n");

  for(int i = 0; i < row; ++i)
  {
    printf("%s\n", path_arr[i]);
  }

  return true;
}

