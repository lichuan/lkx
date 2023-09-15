#include <stddef.h>
#include "lkx/container/rbtree.h"

bool lkx_rb_find_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node **node)
{
  lkx_RB_Node *last_query = tree->last_query;

  if(last_query != NULL)
  {
    if(key == last_query->k64)
    {
      *node = last_query;
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
      *node = cur;
      return true;
    }

    if(key > cur->k64)
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

bool lkx_rb_find_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node **node)
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
          if(kstr->length < 22)
          {
            *node = last_query;
            return true;
          }

          unsigned char *s1 = key->data + key->start_idx + 22;
          unsigned char *s2 = kstr->data + kstr->start_idx + 22;

          while(*s1 == *s2++)
          {
            if(*s1++ == 0)
            {
              *node = last_query;
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
            *node = last_query;
            return true;
          }
        }
      }
    }
  }

  lkx_RB_Node *cur = tree->root;
  
  if(cur == NULL)
  {
    return false;
  }

  if(cur->kstr->hash_id1 != 0)
  {
    while(true)
    {
      lkx_String *kstr = cur->kstr;
      
      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
      }
      else if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
      }
      else if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
      }
      else if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
      }
      else
      {
        if(kstr->length < 22)
        {
          *node = cur;
          return true;
        }

        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            *node = cur;
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

      if(cur == NULL)
      {
        return false;
      }
    }

    return false;
  }

  while(true)
  {
    lkx_String *kstr = cur->kstr;
    unsigned char *s1 = key->data + key->start_idx;
    unsigned char *s2 = kstr->data + kstr->start_idx;

    while(*s1 == *s2++)
    {
      if(*s1++ == 0)
      {
        *node = cur;
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

    if(cur == NULL)
    {
      return false;
    }
  }
  
  return false;
}

bool lkx_rb_exist_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node **node)
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
    }
    else
    {
      cur = cur->left;
    }
  }

  return false;
}

bool lkx_rb_exist_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node **node)
{
  lkx_RB_Node *cur = tree->root;

  if(cur == NULL)
  {
    return false;
  }
  
  if(cur->kstr->hash_id1 != 0)
  {
    while(true)
    {
      lkx_String *kstr = cur->kstr;
      
      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
      }
      else if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
      }
      else if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
      }
      else if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
      }
      else
      {
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
      }

      if(cur == NULL)
      {
        return false;
      }
    }

    return false;
  }

  while(true)
  {
    lkx_String *kstr = cur->kstr;
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

    if(cur == NULL)
    {
      return false;
    }
  }

  return false;
}

bool lkx_rb_insert_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node, lkx_RB_Node **replaced_node)
{
  if(tree->root == NULL)
  {
    tree->root = node;
    return false;
  }

  if(key == tree->root->k64)
  {
    if(tree->last_query == tree->root)
    {
      tree->last_query = NULL;
    }

    *replaced_node = tree->root;
    node->color = RB_COLOR_BLACK;
    node->left = tree->root->left;
    node->right = tree->root->right;
    tree->root = node;
    return true;
  }

  lkx_RB_Node *cur = tree->root;
  lkx_RB_Node *parent;
  bool left;

  while(true)
  {
    parent = cur;

    if(key < cur->k64)
    {
      cur = cur->left;
      left = true;
    }
    else
    {
      cur = cur->right;
      left = false;
    }

    if(cur == NULL)
    {
      node->parent = parent;

      if(left)
      {
        parent->left = node;
      }
      else
      {
        parent->right = node;
      }
      
      if(parent->color == RB_COLOR_BLACK)
      {
        return false;
      }

      break;
    }

    if(key == cur->k64)
    {
      if(tree->last_query == cur)
      {
        tree->last_query = NULL;
      }

      *replaced_node = cur;
      node->color = cur->color;
      node->parent = parent;
      node->left = cur->left;
      node->right = cur->right;

      if(left)
      {
        parent->left = node;
      }
      else
      {
        parent->right = node;
      }

      return true;
    }
  }

  cur = node;
  lkx_RB_Node *grandpa, *uncle;
  bool parent_left;

check_uncle:
  grandpa = parent->parent;

  if(parent == grandpa->left)
  {
    parent_left = true;
    uncle = grandpa->right;
  }
  else
  {
    parent_left = false;
    uncle = grandpa->left;
  }

  if(uncle != NULL && uncle->color == RB_COLOR_RED)
  {
    parent->color = RB_COLOR_BLACK;
    uncle->color = RB_COLOR_BLACK;

    if(grandpa->parent == NULL)
    {
      return false;
    }

    grandpa->color = RB_COLOR_RED;

    if(grandpa->parent->color == RB_COLOR_BLACK)
    {
      return false;
    }

    cur = grandpa;
    parent = grandpa->parent;
    goto check_uncle;
  }

  if(cur == parent->left)
  {
    left = true;
  }
  else
  {
    left = false;
  }

  lkx_RB_Node *grandpa_parent = grandpa->parent;

  if(parent_left)
  {
    if(left)
    {
      if(grandpa_parent == NULL)
      {
        tree->root = parent;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = parent;
      }
      else
      {
        grandpa_parent->right = parent;
      }

      parent->parent = grandpa_parent;
      parent->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->left = parent->right;

      if(uncle != NULL)
      {
        parent->right->parent = grandpa;
      }

      parent->right = grandpa;
      grandpa->parent = parent;
    }
    else
    {
      if(grandpa_parent == NULL)
      {
        tree->root = cur;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = cur;
      }
      else
      {
        grandpa_parent->right = cur;
      }

      cur->parent = grandpa_parent;
      cur->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->left = cur->right;
      parent->right = cur->left;
      
      if(uncle != NULL)
      {
        cur->right->parent = grandpa;
        cur->left->parent = parent;
      }

      cur->right = grandpa;
      grandpa->parent = cur;
      cur->left = parent;
      parent->parent = cur;
    }
  }
  else
  {
    if(left)
    {
      if(grandpa_parent == NULL)
      {
        tree->root = cur;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = cur;
      }
      else
      {
        grandpa_parent->right = cur;
      }

      cur->parent = grandpa_parent;
      cur->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->right = cur->left;
      parent->left = cur->right;
      
      if(uncle != NULL)
      {
        cur->left->parent = grandpa;
        cur->right->parent = parent;
      }

      cur->left = grandpa;
      grandpa->parent = cur;
      cur->right = parent;
      parent->parent = cur;
    }
    else
    {
      if(grandpa_parent == NULL)
      {
        tree->root = parent;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = parent;
      }
      else
      {
        grandpa_parent->right = parent;
      }

      parent->parent = grandpa_parent;
      parent->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->right = parent->left;

      if(uncle != NULL)
      { 
        parent->left->parent = grandpa;
      }

      parent->left = grandpa;
      grandpa->parent = parent;
    }
  }

  return false;  
}

bool lkx_rb_insert_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node, lkx_RB_Node **replaced_node)
{
  if(tree->root == NULL)
  {
    tree->root = node;
    return false;
  }

  lkx_String *kstr = tree->root->kstr;
  lkx_RB_Node *cur = tree->root;
  lkx_RB_Node *parent;
  bool left;

  if(kstr->hash_id1 != 0)
  {
    if(key->hash_id1 == kstr->hash_id1 && key->hash_id2 == kstr->hash_id2)
    {
      if(kstr->length < 22)
      {
        if(tree->last_query == tree->root)
        {
          tree->last_query = NULL;
        }

        *replaced_node = tree->root;
        node->color = RB_COLOR_BLACK;
        node->left = tree->root->left;
        node->right = tree->root->right;
        tree->root = node;
        return true;
      }
      
      unsigned char *s1 = key->data + key->start_idx + 22;
      unsigned char *s2 = kstr->data + kstr->start_idx + 22;

      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
          if(tree->last_query == tree->root)
          {
            tree->last_query = NULL;
          }
          
          *replaced_node = tree->root;
          node->color = RB_COLOR_BLACK;
          node->left = tree->root->left;
          node->right = tree->root->right;
          tree->root = node;
          return true;
        }
      }
    }

    while(true)
    {
      parent = cur;
      kstr = cur->kstr;

      if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
        left = true;
      }
      else if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
        left = false;
      }
      else if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
        left = true;
      }
      else if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
        left = false;
      }
      else
      {
        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1++ == *s2++);
        --s2;
        --s1;

        if(*s1 > *s2)
        {
          cur = cur->right;
          left = false;
        }
        else
        {
          cur = cur->left;
          left = true;
        }
      }

      if(cur == NULL)
      {
        node->parent = parent;

        if(left)
        {
          parent->left = node;
        }
        else
        {
          parent->right = node;
        }
        
        if(parent->color == RB_COLOR_BLACK)
        {
          return false;
        }

        break;
      }

      kstr = cur->kstr;

      if(key->hash_id1 == kstr->hash_id1 && key->hash_id2 == kstr->hash_id2)
      {
        if(kstr->length < 22)
        {
          if(tree->last_query == cur)
          {
            tree->last_query = NULL;
          }

          *replaced_node = cur;
          node->color = cur->color;
          node->parent = parent;
          node->left = cur->left;
          node->right = cur->right;

          if(left)
          {
            parent->left = node;
          }
          else
          {
            parent->right = node;
          }

          return true;
        }
        
        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            if(tree->last_query == cur)
            {
              tree->last_query = NULL;
            }

            *replaced_node = cur;
            node->color = cur->color;
            node->parent = parent;
            node->left = cur->left;
            node->right = cur->right;

            if(left)
            {
              parent->left = node;
            }
            else
            {
              parent->right = node;
            }

            return true;
          }
        }
      }
    }
  }
  else
  {
    unsigned char *s1 = key->data + key->start_idx;
    unsigned char *s2 = kstr->data + kstr->start_idx;

    if(key->length == kstr->length)
    {
      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
          if(tree->last_query == tree->root)
          {
            tree->last_query = NULL;
          }

          *replaced_node = tree->root;
          node->color = RB_COLOR_BLACK;
          node->left = tree->root->left;
          node->right = tree->root->right;
          tree->root = node;
          return true;
        }
      }
    }

    while(true)
    {
      parent = cur;
      kstr = cur->kstr;
      unsigned char *s1 = key->data + key->start_idx;
      unsigned char *s2 = kstr->data + kstr->start_idx;
      while(*s1++ == *s2++);
      --s1;
      --s2;

      if(*s1 < *s2)
      {
        cur = cur->left;
        left = true;
      }
      else
      {
        cur = cur->right;
        left = false;
      }

      if(cur == NULL)
      {
        node->parent = parent;

        if(left)
        {
          parent->left = node;
        }
        else
        {
          parent->right = node;
        }
        
        if(parent->color == RB_COLOR_BLACK)
        {
          return false;
        }

        break;
      }

      kstr = cur->kstr;
      s1 = key->data + key->start_idx;
      s2 = kstr->data + kstr->start_idx;

      if(key->length == kstr->length)
      {
        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            if(tree->last_query == cur)
            {
              tree->last_query = NULL;
            }
            
            *replaced_node = cur;
            node->color = cur->color;
            node->parent = parent;
            node->left = cur->left;
            node->right = cur->right;

            if(left)
            {
              parent->left = node;
            }
            else
            {
              parent->right = node;
            }

            return true;
          }
        }
      }
    }
  }
  
  cur = node;
  lkx_RB_Node *grandpa, *uncle;
  bool parent_left;

check_uncle:
  grandpa = parent->parent;

  if(parent == grandpa->left)
  {
    parent_left = true;
    uncle = grandpa->right;
  }
  else
  {
    parent_left = false;
    uncle = grandpa->left;
  }

  if(uncle != NULL && uncle->color == RB_COLOR_RED)
  {
    parent->color = RB_COLOR_BLACK;
    uncle->color = RB_COLOR_BLACK;

    if(grandpa->parent == NULL)
    {
      return false;
    }

    grandpa->color = RB_COLOR_RED;

    if(grandpa->parent->color == RB_COLOR_BLACK)
    {
      return false;
    }

    cur = grandpa;
    parent = grandpa->parent;
    goto check_uncle;
  }

  if(cur == parent->left)
  {
    left = true;
  }
  else
  {
    left = false;
  }

  lkx_RB_Node *grandpa_parent = grandpa->parent;

  if(parent_left)
  {
    if(left)
    {
      if(grandpa_parent == NULL)
      {
        tree->root = parent;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = parent;
      }
      else
      {
        grandpa_parent->right = parent;
      }

      parent->parent = grandpa_parent;
      parent->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->left = parent->right;

      if(uncle != NULL)
      {
        parent->right->parent = grandpa;
      }

      parent->right = grandpa;
      grandpa->parent = parent;
    }
    else
    {
      if(grandpa_parent == NULL)
      {
        tree->root = cur;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = cur;
      }
      else
      {
        grandpa_parent->right = cur;
      }

      cur->parent = grandpa_parent;
      cur->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->left = cur->right;
      parent->right = cur->left;
      
      if(uncle != NULL)
      {
        cur->right->parent = grandpa;
        cur->left->parent = parent;
      }

      cur->right = grandpa;
      grandpa->parent = cur;
      cur->left = parent;
      parent->parent = cur;
    }
  }
  else
  {
    if(left)
    {
      if(grandpa_parent == NULL)
      {
        tree->root = cur;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = cur;
      }
      else
      {
        grandpa_parent->right = cur;
      }

      cur->parent = grandpa_parent;
      cur->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->right = cur->left;
      parent->left = cur->right;
      
      if(uncle != NULL)
      {
        cur->left->parent = grandpa;
        cur->right->parent = parent;
      }

      cur->left = grandpa;
      grandpa->parent = cur;
      cur->right = parent;
      parent->parent = cur;
    }
    else
    {
      if(grandpa_parent == NULL)
      {
        tree->root = parent;
      }
      else if(grandpa == grandpa_parent->left)
      {
        grandpa_parent->left = parent;
      }
      else
      {
        grandpa_parent->right = parent;
      }

      parent->parent = grandpa_parent;
      parent->color = RB_COLOR_BLACK;
      grandpa->color = RB_COLOR_RED;
      grandpa->right = parent->left;

      if(uncle != NULL)
      { 
        parent->left->parent = grandpa;
      }

      parent->left = grandpa;
      grandpa->parent = parent;
    }
  }

  return false;
}
