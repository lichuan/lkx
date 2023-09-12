#include <stddef.h>
#include "lkx/container/rbtree.h"

bool lkx_rb_find_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node)
{
  lkx_RB_Node *last_query = tree->last_query;

  if(last_query != NULL)
  {
    if(key == last_query->k64)
    {
      *node = *last_query;
      return true;
    }
  }

  lkx_RB_Node *cur = tree->root;

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    if(key == cur->k64)
    {
      *node = *cur;
      return true;
    }

    if(key > cur->k64)
    {
      cur = cur->right;
    } else
    {
      cur = cur->left;
    }
  }

  return false;
}

bool lkx_rb_find_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node)
{
  lkx_RB_Node *last_query = tree->last_query;

  if(last_query != NULL)
  {
    lkx_String *kstr = last_query->kstr;

    if(key->length == kstr->length)
    {
      if(kstr->hash_id1 != 0)
      {
        if(kstr->hash_id1 == key->hash_id1 && kstr->hash_id2 == key->hash_id2)
        {
          if(kstr->length <= 22)
          {
            *node = *last_query;
            return true;
          }

          unsigned char *s1 = key->data + key->start_idx + 22;
          unsigned char *s2 = kstr->data + kstr->start_idx + 22;

          while(*s1 == *s2++)
          {
            if(*s1++ == 0)
            {
              *node = *last_query;
              return true;
            }
          }
        }
      }
      else
      {
        unsigned char *s1 = key->data + key->start_idx;
        unsigned char *s2 = kstr->data + kstr->start_idx;
        
        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            *node = *last_query;
            return true;
          }
        }
      }
    }
  }

  lkx_RB_Node *cur = tree->root;

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    lkx_String *kstr = cur->kstr;

    if(kstr->hash_id1 != 0)
    {
      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
        continue;
      }

      if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
        continue;
      }

      if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
        continue;
      }

      if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
        continue;
      }

      if(kstr->length < 22)
      {
        *node = *cur;
        return true;
      }

      unsigned char *s1 = key->data + key->start_idx + 22;
      unsigned char *s2 = kstr->data + kstr->start_idx + 22;

      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
          *node = *cur;
          return true;
        }
      }

      --s2;

      if(*s1 > *s2)
      {
        cur = cur->right;
      }
      else
      {
        cur = cur->left;
      }

      continue;
    }

    unsigned char *s1 = key->data + key->start_idx;
    unsigned char *s2 = kstr->data + kstr->start_idx;

    while(*s1 == *s2++)
    {
      if(*s1++ == 0)
      {
        *node = *cur;
        return true;
      }
    }

    --s2;

    if(*s1 > *s2)
    {
      cur = cur->right;
    }
    else
    {
      cur = cur->left;
    }
  }

  return false;
}

bool lkx_rb_exist_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node)
{
  lkx_RB_Node *cur = tree->root;

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    if(key == cur->k64)
    {
      tree->last_query = cur;
      return true;
    }

    if(key > cur->k64)
    {
      cur = cur->right;
    } else
    {
      cur = cur->left;
    }
  }

  return false;
}

bool lkx_rb_exist_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node)
{
  lkx_RB_Node *cur = tree->root;

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    lkx_String *kstr = cur->kstr;

    if(kstr->hash_id1 != 0)
    {
      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
        continue;
      }

      if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
        continue;
      }

      if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
        continue;
      }

      if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
        continue;
      }

      if(kstr->length < 22)
      {
        tree->last_query = cur;
        return true;
      }

      unsigned char *s1 = key->data + key->start_idx + 22;
      unsigned char *s2 = kstr->data + kstr->start_idx + 22;

      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
          tree->last_query = cur;
          return true;
        }
      }

      --s2;

      if(*s1 > *s2)
      {
        cur = cur->right;
      }
      else
      {
        cur = cur->left;
      }

      continue;
    }

    unsigned char *s1 = key->data + key->start_idx;
    unsigned char *s2 = kstr->data + kstr->start_idx;

    while(*s1 == *s2++)
    {
      if(*s1++ == 0)
      {
        tree->last_query = cur;
        return true;
      }
    }

    --s2;

    if(*s1 > *s2)
    {
      cur = cur->right;
    }
    else
    {
      cur = cur->left;
    }
  }

  return false;
}
