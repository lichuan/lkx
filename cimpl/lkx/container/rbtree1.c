#include <stddef.h>
#include <stdlib.h>
#include "lkx/container/rbtree1.h"

void lkx_free_node1(lkx_RB_Node1 *node)
{
  lkx_free_str(node->kstr);
  free(node);
}

bool lkx_rb_1_exist_k64(lkx_RB_Tree1 *tree, int64 key)
{
  lkx_RB_Node1 *cur = tree->root;

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    if(key == cur->k64)
    {
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

bool lkx_rb_1_exist_kstr(lkx_RB_Tree1 *tree, lkx_String *key)
{
  lkx_RB_Node1 *cur = tree->root;
  
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
          return true;
        }

        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
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
  }
  else
  {
    while(true)
    {
      lkx_String *kstr = cur->kstr;
      unsigned char *s1 = key->data + key->start_idx;
      unsigned char *s2 = kstr->data + kstr->start_idx;

      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
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
  }

  return false;
}

bool lkx_rb_1_insert_k64(lkx_RB_Tree1 *tree, int64 key)
{
  lkx_RB_Node1 *node = calloc(1, sizeof(lkx_RB_Node1));
  node->k64 = key;

  if(tree->root == NULL)
  {
    tree->root = node;
    node->color = RB_COLOR_BLACK;
    return true;
  }

  if(key == tree->root->k64)
  {
    free(node);
    return false;
  }

  lkx_RB_Node1 *cur = tree->root;
  lkx_RB_Node1 *parent;
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
        return true;
      }

      break;
    }

    if(key == cur->k64)
    {
      free(node);
      return false;
    }
  }

  cur = node;
  lkx_RB_Node1 *grandpa, *uncle;
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
      return true;
    }

    grandpa->color = RB_COLOR_RED;

    if(grandpa->parent->color == RB_COLOR_BLACK)
    {
      return true;
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

  lkx_RB_Node1 *grandpa_parent = grandpa->parent;

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

  return true;  
}

bool lkx_rb_1_insert_kstr(lkx_RB_Tree1 *tree, lkx_String *key)
{
  lkx_RB_Node1 *node = calloc(1, sizeof(lkx_RB_Node1));
  node->kstr = key;

  if(tree->root == NULL)
  {
    tree->root = node;
    node->color = RB_COLOR_BLACK;
    return true;
  }

  lkx_String *kstr = tree->root->kstr;

  if(key->length == kstr->length)
  {
    if(kstr->hash_id1 != 0)
    {
      if(key->hash_id1 == kstr->hash_id1 && key->hash_id2 == kstr->hash_id2)
      {
        if(kstr->length < 22)
        {
          lkx_free_node1(node);
          return false;
        }

        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            lkx_free_node1(node);
            return false;
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
          lkx_free_node1(node);
          return false;
        }
      }
    }
  }
  
  lkx_RB_Node1 *cur = tree->root;
  lkx_RB_Node1 *parent;
  bool left;

  if(cur->kstr->hash_id1 != 0)
  {
    while(true)
    {
      kstr = cur->kstr;
      parent = cur;
            
      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
        left = false;
      }
      else if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
        left = true;
      }
      else if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
        left = false;
      }
      else if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
        left = true;
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
          return true;
        }

        break;
      }

      kstr = cur->kstr;

      if(key->length == kstr->length)
      {
        if(key->hash_id1 == kstr->hash_id1 && key->hash_id2 == kstr->hash_id2)
        {
          if(kstr->length < 22)
          {
            lkx_free_node1(node);
            return false;
          }
          else
          {
            unsigned char *s1 = key->data + key->start_idx + 22;
            unsigned char *s2 = kstr->data + kstr->start_idx + 22;

            while(*s1 == *s2++)
            {
              if(*s1++ == 0)
              {
                lkx_free_node1(node);
                return false;
              }
            }
          }
        }
      }
    }
  }
  else
  {
    while(true)
    {
      parent = cur;
      kstr = cur->kstr;
      unsigned char *s1 = key->data + key->start_idx;
      unsigned char *s2 = kstr->data + kstr->start_idx;

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
          return true;
        }

        break;
      }

      kstr = cur->kstr;

      if(key->length == kstr->length)
      {
        unsigned char *s1 = key->data + key->start_idx;
        unsigned char *s2 = kstr->data + kstr->start_idx;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            lkx_free_node1(node);
            return false;
          }
        }
      }
    }
  }
  
  cur = node;
  lkx_RB_Node1 *grandpa, *uncle;
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
      return true;
    }

    grandpa->color = RB_COLOR_RED;

    if(grandpa->parent->color == RB_COLOR_BLACK)
    {
      return true;
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

  lkx_RB_Node1 *grandpa_parent = grandpa->parent;

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
  
  lkx_free_node1(node);
  return false;
}

bool lkx_rb_1_erase_k64(lkx_RB_Tree1 *tree, int64 key)
{
  lkx_RB_Node1 *cur = tree->root;
  bool left;
  lkx_RB_Node1 *parent, *brother;
  lkx_RB_Node1 null_node = {.color = RB_COLOR_BLACK};

  while(true)
  {
    if(cur == NULL)
    {
      return false;
    }

    parent = cur->parent;

    if(key = cur->k64)
    {
      lkx_RB_Node1 *left_child = cur->left;
      lkx_RB_Node1 *right_child = cur->right;

      if(left_child == NULL && right_child == NULL)
      {
        if(cur == tree->root)
        {
          free(cur);
          tree->root = NULL;
          return true;
        }

        if(left)
        {
          parent->left = NULL;
        }
        else
        {
          parent->right = NULL;
        }

        if(cur->color == RB_COLOR_RED)
        {
          free(cur);
          return true;
        }

        null_node = *cur;
        goto black_leaf;
      }
      else if(left_child != NULL && right_child != NULL)
      {
        lkx_RB_Node1 *r_left = right_child;

        while(r_left->left != NULL)
        {
          r_left = r_left->left;
        }
        
        if(cur == tree->root)
        {
          tree->root = r_left;
        }
        else if(left)
        {
          parent->left = r_left;
        }
        else
        {
          parent->right = r_left;
        }

        lkx_RB_COLOR r_left_color = r_left->color;
        r_left->color = cur->color;
        r_left->left = cur->left;
        cur->left->parent = r_left;

        if(r_left == right_child)
        {
          r_left->parent = parent;

          if(r_left_color == RB_COLOR_RED)
          {
            free(cur);
            return true;
          }

          if(right_child->right != NULL)
          {
            right_child->right->color = RB_COLOR_BLACK;
            free(cur);
            return true;
          }

          r_left->right = NULL;
          null_node.parent = r_left;
          left = false;
          goto black_leaf;
        }
        
        if(r_left_color == RB_COLOR_RED)
        {
          r_left->parent->left = NULL;
          r_left->parent = parent;
          r_left->right = cur->right;
          cur->right->parent = r_left;
          free(cur);
          return true;
        }

        if(r_left->right != NULL)
        {
          r_left->right->color = RB_COLOR_BLACK;
          r_left->parent->left = r_left->right;
          r_left->right->parent = r_left->parent;
          r_left->parent = parent;
          r_left->right = cur->right;
          cur->right->parent = r_left;
          free(cur);
          return true;
        }

        left = true;
        null_node.parent = r_left->parent;
        r_left->parent->left = NULL;
        r_left->parent = parent;
        r_left->right = cur->right;
        cur->right->parent = r_left;
        goto black_leaf;
      }
      else if(left_child != NULL)
      {
        left_child->color = RB_COLOR_BLACK;

        if(cur == tree->root)
        {
          tree->root = left_child;
          left_child->parent = NULL;
          free(cur);
          return true;
        }

        if(left)
        {
          parent->left = left_child;
        }
        else
        {
          parent->right = left_child;
        }

        left_child->parent = parent;
      }
      else
      {
        right_child->color = RB_COLOR_BLACK;

        if(cur == tree->root)
        {
          tree->root = right_child;
          right_child->parent = NULL;
          free(cur);
          return true;
        }

        if(left)
        {
          parent->left = right_child;
        }
        else
        {
          parent->right = right_child;
        }

        right_child->parent = parent;
      }

      free(cur);
      return true;
    }

    if(key > cur->k64)
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

black_leaf:
  parent = null_node.parent;

  if(left)
  {
    brother = parent->right;

    if(brother->color == RB_COLOR_BLACK)
    {
      if(brother->right != NULL && brother->right->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother;
          brother->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother;
          }
          else
          {
            grandpa->right = brother;
          }
        }
        
        parent->right = brother->left;

        if(brother->left != NULL)
        {
          brother->left->parent = parent;
        }
        
        brother->left = parent;
        parent->parent = brother;
        brother->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->right->color = RB_COLOR_BLACK;
        free(cur);
        return true;
      }

      if(brother->left != NULL && brother->left->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother->left;
          brother->left->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->left->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother->left;
          }
          else
          {
            grandpa->right = brother->left;
          }
        }
        
        parent->right = brother->left->left;

        if(brother->left->left != NULL)
        {
          brother->left->left->parent = parent;
        }
        
        brother->left->left = parent;
        parent->parent = brother->left;
        brother->left->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->left = brother->left->right;

        if(brother->left->right != NULL)
        {
          brother->left->right->parent = brother;
        }
        
        free(cur);
        return true;
      }

      brother->color = RB_COLOR_RED;

      if(parent->color == RB_COLOR_RED)
      { 
        parent->color = RB_COLOR_BLACK;
        free(cur);
        return true;
      }

      if(parent == tree->root)
      {
        free(cur);
        return true;
      }

      null_node = *parent;

      if(parent == parent->parent->right)
      {
        left = false;
      }

      goto black_leaf;
    }

    if(parent == tree->root)
    {
      tree->root = brother;
      brother->parent = NULL;
    }
    else
    {
      lkx_RB_Node1 *grandpa = parent->parent;
      brother->parent = grandpa;
      
      if(parent == grandpa->left)
      {
        grandpa->left = brother;
      }
      else
      {
        grandpa->right = brother;
      }
    }

    brother->color = RB_COLOR_BLACK;
    parent->color = RB_COLOR_RED;
    parent->right = brother->left;
    brother->left->parent = parent;
    parent->parent = brother;
    brother->left = parent;
    goto black_leaf;
  }
  else
  {
    brother = parent->left;

    if(brother->color == RB_COLOR_BLACK)
    {
      if(brother->left != NULL && brother->left->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother;
          brother->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother;
          }
          else
          {
            grandpa->right = brother;
          }
        }
        
        parent->left = brother->right;

        if(brother->right != NULL)
        {
          brother->right->parent = parent;
        }
        
        brother->right = parent;
        parent->parent = brother;
        brother->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->left->color = RB_COLOR_BLACK;
        free(cur);
        return true;
      }

      if(brother->right != NULL && brother->right->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother->right;
          brother->right->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->right->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother->right;
          }
          else
          {
            grandpa->right = brother->right;
          }
        }
        
        parent->left = brother->right->right;

        if(brother->right->right != NULL)
        {
          brother->right->right->parent = parent;
        }
        
        brother->right->right = parent;
        parent->parent = brother->right;
        brother->right->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->right = brother->right->left;

        if(brother->right->left != NULL)
        {
          brother->right->left->parent = brother;
        }
        
        free(cur);
        return true;
      }

      brother->color = RB_COLOR_RED;

      if(parent->color == RB_COLOR_RED)
      { 
        parent->color = RB_COLOR_BLACK;
        free(cur);
        return true;
      }

      if(parent == tree->root)
      {
        free(cur);
        return true;
      }

      null_node = *parent;

      if(parent == parent->parent->left)
      {
        left = true;
      }

      goto black_leaf;
    }

    if(parent == tree->root)
    {
      tree->root = brother;
      brother->parent = NULL;
    }
    else
    {
      lkx_RB_Node1 *grandpa = parent->parent;
      brother->parent = grandpa;
      
      if(parent == grandpa->left)
      {
        grandpa->left = brother;
      }
      else
      {
        grandpa->right = brother;
      }
    }

    brother->color = RB_COLOR_BLACK;
    parent->color = RB_COLOR_RED;
    parent->left = brother->right;
    brother->right->parent = parent;
    parent->parent = brother;
    brother->right = parent;
    goto black_leaf;
  }
  
  free(cur);
  return true;
}

bool lkx_rb_1_erase_kstr(lkx_RB_Tree1 *tree, lkx_String *key)
{
  lkx_RB_Node1 *cur = tree->root;
  bool left;
  lkx_RB_Node1 *parent, *brother;
  lkx_RB_Node1 null_node = {.color = RB_COLOR_BLACK};

  if(cur == NULL)
  {
    return false;
  }

  lkx_String *kstr = cur->kstr;

  if(kstr->hash_id1 != 0)
  {
    while(true)
    {
      parent = cur->parent;
      kstr = cur->kstr;

      if(key->hash_id1 > kstr->hash_id1)
      {
        cur = cur->right;
        left = false;
      }
      else if(key->hash_id1 < kstr->hash_id1)
      {
        cur = cur->left;
        left = true;
      }
      else if(key->hash_id2 > kstr->hash_id2)
      {
        cur = cur->right;
        left = false;
      }
      else if(key->hash_id2 < kstr->hash_id2)
      {
        cur = cur->left;
        left = true;
      }
      else
      {
        if(kstr->length < 22)
        {
          lkx_RB_Node1 *left_child = cur->left;
          lkx_RB_Node1 *right_child = cur->right;

          if(left_child == NULL && right_child == NULL)
          {
            if(cur == tree->root)
            {
              tree->root = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = NULL;
            }
            else
            {
              parent->right = NULL;
            }

            if(cur->color == RB_COLOR_RED)
            {
              lkx_free_node1(cur);
              return true;
            }

            null_node = *cur;
            goto black_leaf;
          }
          else if(left_child != NULL && right_child != NULL)
          {
            lkx_RB_Node1 *r_left = right_child;

            while(r_left->left != NULL)
            {
              r_left = r_left->left;
            }
            
            if(cur == tree->root)
            {
              tree->root = r_left;
            }
            else if(left)
            {
              parent->left = r_left;
            }
            else
            {
              parent->right = r_left;
            }

            lkx_RB_COLOR r_left_color = r_left->color;
            r_left->color = cur->color;
            r_left->left = cur->left;
            cur->left->parent = r_left;

            if(r_left == right_child)
            {
              r_left->parent = parent;

              if(r_left_color == RB_COLOR_RED)
              {
                lkx_free_node1(cur);
                return true;
              }

              if(right_child->right != NULL)
              {
                right_child->right->color = RB_COLOR_BLACK;
                lkx_free_node1(cur);
                return true;
              }

              r_left->right = NULL;
              null_node.parent = r_left;
              left = false;
              goto black_leaf;
            }
            
            if(r_left_color == RB_COLOR_RED)
            {
              r_left->parent->left = NULL;
              r_left->parent = parent;
              r_left->right = cur->right;
              cur->right->parent = r_left;
              lkx_free_node1(cur);
              return true;
            }

            if(r_left->right != NULL)
            {
              r_left->right->color = RB_COLOR_BLACK;
              r_left->parent->left = r_left->right;
              r_left->right->parent = r_left->parent;
              r_left->parent = parent;
              r_left->right = cur->right;
              cur->right->parent = r_left;
              lkx_free_node1(cur);
              return true;
            }

            left = true;
            null_node.parent = r_left->parent;
            r_left->parent->left = NULL;
            r_left->parent = parent;
            r_left->right = cur->right;
            cur->right->parent = r_left;
            goto black_leaf;
          }
          else if(left_child != NULL)
          {
            left_child->color = RB_COLOR_BLACK;

            if(cur == tree->root)
            {
              tree->root = left_child;
              left_child->parent = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = left_child;
            }
            else
            {
              parent->right = left_child;
            }

            left_child->parent = parent;
          }
          else
          {
            right_child->color = RB_COLOR_BLACK;

            if(cur == tree->root)
            {
              tree->root = right_child;
              right_child->parent = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = right_child;
            }
            else
            {
              parent->right = right_child;
            }

            right_child->parent = parent;
          }

          lkx_free_node1(cur);
          return true;
        }

        unsigned char *s1 = key->data + key->start_idx + 22;
        unsigned char *s2 = kstr->data + kstr->start_idx + 22;

        while(*s1 == *s2++)
        {
          if(*s1++ == 0)
          {
            lkx_RB_Node1 *left_child = cur->left;
            lkx_RB_Node1 *right_child = cur->right;

            if(left_child == NULL && right_child == NULL)
            {
              if(cur == tree->root)
              {
                tree->root = NULL;
                lkx_free_node1(cur);
                return true;
              }

              if(left)
              {
                parent->left = NULL;
              }
              else
              {
                parent->right = NULL;
              }

              if(cur->color == RB_COLOR_RED)
              {
                lkx_free_node1(cur);
                return true;
              }

              null_node = *cur;
              goto black_leaf;
            }
            else if(left_child != NULL && right_child != NULL)
            {
              lkx_RB_Node1 *r_left = right_child;

              while(r_left->left != NULL)
              {
                r_left = r_left->left;
              }
              
              if(cur == tree->root)
              {
                tree->root = r_left;
              }
              else if(left)
              {
                parent->left = r_left;
              }
              else
              {
                parent->right = r_left;
              }

              lkx_RB_COLOR r_left_color = r_left->color;
              r_left->color = cur->color;
              r_left->left = cur->left;
              cur->left->parent = r_left;

              if(r_left == right_child)
              {
                r_left->parent = parent;

                if(r_left_color == RB_COLOR_RED)
                {
                  lkx_free_node1(cur);
                  return true;
                }

                if(right_child->right != NULL)
                {
                  right_child->right->color = RB_COLOR_BLACK;
                  lkx_free_node1(cur);
                  return true;
                }

                r_left->right = NULL;
                null_node.parent = r_left;
                left = false;
                goto black_leaf;
              }
              
              if(r_left_color == RB_COLOR_RED)
              {
                r_left->parent->left = NULL;
                r_left->parent = parent;
                r_left->right = cur->right;
                cur->right->parent = r_left;
                lkx_free_node1(cur);
                return true;
              }

              if(r_left->right != NULL)
              {
                r_left->right->color = RB_COLOR_BLACK;
                r_left->parent->left = r_left->right;
                r_left->right->parent = r_left->parent;
                r_left->parent = parent;
                r_left->right = cur->right;
                cur->right->parent = r_left;
                lkx_free_node1(cur);
                return true;
              }

              left = true;
              null_node.parent = r_left->parent;
              r_left->parent->left = NULL;
              r_left->parent = parent;
              r_left->right = cur->right;
              cur->right->parent = r_left;
              goto black_leaf;
            }
            else if(left_child != NULL)
            {
              left_child->color = RB_COLOR_BLACK;

              if(cur == tree->root)
              {
                tree->root = left_child;
                left_child->parent = NULL;
                lkx_free_node1(cur);
                return true;
              }

              if(left)
              {
                parent->left = left_child;
              }
              else
              {
                parent->right = left_child;
              }

              left_child->parent = parent;
            }
            else
            {
              right_child->color = RB_COLOR_BLACK;

              if(cur == tree->root)
              {
                tree->root = right_child;
                right_child->parent = NULL;
                lkx_free_node1(cur);
                return true;
              }

              if(left)
              {
                parent->left = right_child;
              }
              else
              {
                parent->right = right_child;
              }

              right_child->parent = parent;
            }

            lkx_free_node1(cur);
            return true;
          }
        }

        --s2;

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
        return false;
      }
    }
  }
  else
  {
    while(true)
    {
      parent = cur->parent;
      kstr = cur->kstr;
      unsigned char *s1 = key->data + key->start_idx;
      unsigned char *s2 = kstr->data + kstr->start_idx;

      while(*s1 == *s2++)
      {
        if(*s1++ == 0)
        {
          lkx_RB_Node1 *left_child = cur->left;
          lkx_RB_Node1 *right_child = cur->right;

          if(left_child == NULL && right_child == NULL)
          {
            if(cur == tree->root)
            {
              tree->root = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = NULL;
            }
            else
            {
              parent->right = NULL;
            }

            if(cur->color == RB_COLOR_RED)
            {
              lkx_free_node1(cur);
              return true;
            }

            null_node = *cur;
            goto black_leaf;
          }
          else if(left_child != NULL && right_child != NULL)
          {
            lkx_RB_Node1 *r_left = right_child;

            while(r_left->left != NULL)
            {
              r_left = r_left->left;
            }
            
            if(cur == tree->root)
            {
              tree->root = r_left;
            }
            else if(left)
            {
              parent->left = r_left;
            }
            else
            {
              parent->right = r_left;
            }

            lkx_RB_COLOR r_left_color = r_left->color;
            r_left->color = cur->color;
            r_left->left = cur->left;
            cur->left->parent = r_left;

            if(r_left == right_child)
            {
              r_left->parent = parent;

              if(r_left_color == RB_COLOR_RED)
              {
                lkx_free_node1(cur);
                return true;
              }

              if(right_child->right != NULL)
              {
                right_child->right->color = RB_COLOR_BLACK;
                lkx_free_node1(cur);
                return true;
              }

              r_left->right = NULL;
              null_node.parent = r_left;
              left = false;
              goto black_leaf;
            }
            
            if(r_left_color == RB_COLOR_RED)
            {
              r_left->parent->left = NULL;
              r_left->parent = parent;
              r_left->right = cur->right;
              cur->right->parent = r_left;
              lkx_free_node1(cur);
              return true;
            }

            if(r_left->right != NULL)
            {
              r_left->right->color = RB_COLOR_BLACK;
              r_left->parent->left = r_left->right;
              r_left->right->parent = r_left->parent;
              r_left->parent = parent;
              r_left->right = cur->right;
              cur->right->parent = r_left;
              lkx_free_node1(cur);
              return true;
            }

            left = true;
            null_node.parent = r_left->parent;
            r_left->parent->left = NULL;
            r_left->parent = parent;
            r_left->right = cur->right;
            cur->right->parent = r_left;
            goto black_leaf;
          }
          else if(left_child != NULL)
          {
            left_child->color = RB_COLOR_BLACK;

            if(cur == tree->root)
            {
              tree->root = left_child;
              left_child->parent = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = left_child;
            }
            else
            {
              parent->right = left_child;
            }

            left_child->parent = parent;
          }
          else
          {
            right_child->color = RB_COLOR_BLACK;

            if(cur == tree->root)
            {
              tree->root = right_child;
              right_child->parent = NULL;
              lkx_free_node1(cur);
              return true;
            }

            if(left)
            {
              parent->left = right_child;
            }
            else
            {
              parent->right = right_child;
            }

            right_child->parent = parent;
          }

          lkx_free_node1(cur);
          return true;
        }
      }

      --s2;

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

      if(cur == NULL)
      {
        return false;
      }
    }
  }
  
black_leaf:
  parent = null_node.parent;

  if(left)
  {
    brother = parent->right;

    if(brother->color == RB_COLOR_BLACK)
    {
      if(brother->right != NULL && brother->right->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother;
          brother->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother;
          }
          else
          {
            grandpa->right = brother;
          }
        }
        
        parent->right = brother->left;

        if(brother->left != NULL)
        {
          brother->left->parent = parent;
        }
        
        brother->left = parent;
        parent->parent = brother;
        brother->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->right->color = RB_COLOR_BLACK;
        lkx_free_node1(cur);
        return true;
      }

      if(brother->left != NULL && brother->left->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother->left;
          brother->left->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->left->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother->left;
          }
          else
          {
            grandpa->right = brother->left;
          }
        }
        
        parent->right = brother->left->left;

        if(brother->left->left != NULL)
        {
          brother->left->left->parent = parent;
        }
        
        brother->left->left = parent;
        parent->parent = brother->left;
        brother->left->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->left = brother->left->right;

        if(brother->left->right != NULL)
        {
          brother->left->right->parent = brother;
        }
        
        lkx_free_node1(cur);
        return true;
      }

      brother->color = RB_COLOR_RED;

      if(parent->color == RB_COLOR_RED)
      { 
        parent->color = RB_COLOR_BLACK;
        lkx_free_node1(cur);
        return true;
      }

      if(parent == tree->root)
      {
        lkx_free_node1(cur);
        return true;
      }

      null_node = *parent;

      if(parent == parent->parent->right)
      {
        left = false;
      }

      goto black_leaf;
    }

    if(parent == tree->root)
    {
      tree->root = brother;
      brother->parent = NULL;
    }
    else
    {
      lkx_RB_Node1 *grandpa = parent->parent;
      brother->parent = grandpa;
      
      if(parent == grandpa->left)
      {
        grandpa->left = brother;
      }
      else
      {
        grandpa->right = brother;
      }
    }

    brother->color = RB_COLOR_BLACK;
    parent->color = RB_COLOR_RED;
    parent->right = brother->left;
    brother->left->parent = parent;
    parent->parent = brother;
    brother->left = parent;
    goto black_leaf;
  }
  else
  {
    brother = parent->left;

    if(brother->color == RB_COLOR_BLACK)
    {
      if(brother->left != NULL && brother->left->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother;
          brother->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother;
          }
          else
          {
            grandpa->right = brother;
          }
        }
        
        parent->left = brother->right;

        if(brother->right != NULL)
        {
          brother->right->parent = parent;
        }
        
        brother->right = parent;
        parent->parent = brother;
        brother->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->left->color = RB_COLOR_BLACK;
        lkx_free_node1(cur);
        return true;
      }

      if(brother->right != NULL && brother->right->color == RB_COLOR_RED)
      {
        if(parent == tree->root)
        {
          tree->root = brother->right;
          brother->right->parent = NULL;
        }
        else
        {
          lkx_RB_Node1 *grandpa = parent->parent;
          brother->right->parent = grandpa;

          if(parent == grandpa->left)
          {
            grandpa->left = brother->right;
          }
          else
          {
            grandpa->right = brother->right;
          }
        }
        
        parent->left = brother->right->right;

        if(brother->right->right != NULL)
        {
          brother->right->right->parent = parent;
        }
        
        brother->right->right = parent;
        parent->parent = brother->right;
        brother->right->color = parent->color;
        parent->color = RB_COLOR_BLACK;
        brother->right = brother->right->left;

        if(brother->right->left != NULL)
        {
          brother->right->left->parent = brother;
        }
        
        lkx_free_node1(cur);
        return true;
      }

      brother->color = RB_COLOR_RED;

      if(parent->color == RB_COLOR_RED)
      { 
        parent->color = RB_COLOR_BLACK;
        lkx_free_node1(cur);
        return true;
      }

      if(parent == tree->root)
      {
        lkx_free_node1(cur);
        return true;
      }

      null_node = *parent;

      if(parent == parent->parent->left)
      {
        left = true;
      }

      goto black_leaf;
    }

    if(parent == tree->root)
    {
      tree->root = brother;
      brother->parent = NULL;
    }
    else
    {
      lkx_RB_Node1 *grandpa = parent->parent;
      brother->parent = grandpa;
      
      if(parent == grandpa->left)
      {
        grandpa->left = brother;
      }
      else
      {
        grandpa->right = brother;
      }
    }

    brother->color = RB_COLOR_BLACK;
    parent->color = RB_COLOR_RED;
    parent->left = brother->right;
    brother->right->parent = parent;
    parent->parent = brother;
    brother->right = parent;
    goto black_leaf;
  }

  lkx_free_node1(cur);
  return true;
}
