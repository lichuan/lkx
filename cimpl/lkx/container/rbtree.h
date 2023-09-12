#ifndef __LKX__CONTAINER__RBTREE__
#define __LKX__CONTAINER__RBTREE__

#include "lkx/type/base.h"
#include "lkx/type/string.h"
#include "lkx/container/array.h"
#include "lkx/var.h"

typedef enum lkx_RB_COLOR {
  RB_COLOR_RED,
  RB_COLOR_BLACK
} lkx_RB_COLOR;

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

typedef struct lkx_RB_M_Node {
  lkx_RB_COLOR color;
  struct lkx_RB_M_Node *left;
  struct lkx_RB_M_Node *right;
  struct lkx_RB_M_Node *parent;

  // support multi
  struct lkx_RB_M_Node *next;
  struct lkx_RB_M_Node *prev;
  
  union {
    int64 k64;
    lkx_String *kstr;
  };
  union {
    lkx_Var *data;
    int64 v64;
    double vdbl;
  };
} lkx_RB_M_Node;

typedef struct lkx_RB_Tree {
  lkx_RB_Node *root;
  lkx_RB_Node *left_most;
  lkx_RB_Node *right_most;
  lkx_RB_Node *last_query;
} lkx_RB_Tree;

typedef struct lkx_RB_M_Tree {
  lkx_RB_M_Node *root;
  lkx_RB_M_Node *left_most;
  lkx_RB_M_Node *right_most;
  lkx_RB_M_Node *last_query;
} lkx_RB_M_Tree;

bool lkx_rb_find_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node);
bool lkx_rb_find_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node);
bool lkx_rb_exist_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node);
bool lkx_rb_exist_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node);
bool lkx_rb_insert_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node, lkx_RB_Node *replaced_node);
bool lkx_rb_insert_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node, lkx_RB_Node *replaced_node);
bool lkx_rb_erase_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node);
bool lkx_rb_erase_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node);

bool lkx_rb_m_find_k64(lkx_RB_M_Tree *tree, int64 key, lkx_RB_M_Node *node);
bool lkx_rb_m_find_kstr(lkx_RB_M_Tree *tree, lkx_String *key, lkx_RB_M_Node *node);
bool lkx_rb_m_exist_k64(lkx_RB_Tree *tree, int64 key, lkx_RB_Node *node);
bool lkx_rb_m_exist_kstr(lkx_RB_Tree *tree, lkx_String *key, lkx_RB_Node *node);
bool lkx_rb_m_find_all_k64(lkx_RB_M_Tree *tree, int64 key, lkx_RB_M_Node *node);
bool lkx_rb_m_find_all_kstr(lkx_RB_M_Tree *tree, lkx_String *key, lkx_RB_M_Node *node);
bool lkx_rb_m_insert_k64(lkx_RB_M_Tree *tree, int64 key, lkx_RB_M_Node *node);
bool lkx_rb_m_insert_kstr(lkx_RB_M_Tree *tree, lkx_String *key, lkx_RB_M_Node *node);
bool lkx_rb_m_erase_k64(lkx_RB_M_Tree *tree, int64 key, lkx_RB_M_Node *node);
bool lkx_rb_m_erase_kstr(lkx_RB_M_Tree *tree, lkx_String *key, lkx_RB_M_Node *node);

#endif
