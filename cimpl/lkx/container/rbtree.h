#ifndef __LKX__CONTAINER__RBTREE__
#define __LKX__CONTAINER__RBTREE__

#include "lkx/type/string.h"
#include "lkx/var.h"
#include "lkx/container/base.h"

typedef struct lkx_RB_Node {
  lkx_RB_COLOR color;
  struct lkx_RB_Node *left;
  struct lkx_RB_Node *right;
  struct lkx_RB_Node *parent;

  union {
    int64 k64;
    lkx_String *kstr;
  };
  union {
    lkx_Var *data;
    int64 v64;
    double vdbl;
  };
} lkx_RB_Node;

typedef struct lkx_RB_Tree {
  lkx_RB_Node *root;
  lkx_RB_Node *last_query;
} lkx_RB_Tree;

bool lkx_rb_find_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node **node);
bool lkx_rb_find_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node **node);
bool lkx_rb_exist_k64(lkx_RB_Tree *tree, int64 key);
bool lkx_rb_exist_kstr(lkx_RB_Tree *tree, lkx_String *key);
bool lkx_rb_insert_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node, lkx_RB_Node **replaced_node);
bool lkx_rb_insert_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node, lkx_RB_Node **replaced_node);
bool lkx_rb_erase_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node **node);
bool lkx_rb_erase_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node **node);

#endif
