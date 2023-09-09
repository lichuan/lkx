#ifndef __LKX__CONTAINER__RBTREE__
#define __LKX__CONTAINER__RBTREE__

#include "lkx/type/base.h"
#include "lkx/type/string.h"
#include "lkx/var.h"

typedef enum lkx_RB_Color {
  lkx_RB_Red = 1,
  lkx_RB_Black = 2
} lkx_RB_Color;

typedef struct lkx_RB_Node {
  lkx_RB_Color color;
  struct lkx_RB_Node *left;
  struct lkx_RB_Node *right;
  struct lkx_RB_Node *parent;

  //support multi
  struct lkx_RB_Node *next;
  int64 k64;
  lkx_String *kstr;

  union {
    lkx_Var *data;
    int64 v64;
    double vdbl;
    lkx_String *vstr;
  };
} lkx_RB_Node;

typedef struct lkx_RB_Tree {
  lkx_RB_Node *root;
  lkx_RB_Node *left_most;
  lkx_RB_Node *right_most;

  struct {
    int64 k64;
    lkx_String *kstr;
    union {
      lkx_Var *data;
      int64 v64;
      double vdbl;
      lkx_String *vstr;
    };
  } last_query;
} lkx_RB_Tree;

bool lkx_rb_find_k64_vdbl(lkx_RB_Tree *tree, uint32 key, double *value_ptr);
bool lkx_rb_find_k64_v64(lkx_RB_Tree *tree, int64 key, int64 *value_ptr);
bool lkx_rb_find_k64_var(lkx_RB_Tree *tree, int64 key, lkx_Var **value_ptr);
bool lkx_rb_find_k64_vstr(lkx_RB_Tree *tree, int64 key, lkx_String **value_ptr);
bool lkx_rb_find_kstr_v64(lkx_RB_Tree *tree, lkx_String *key, int64 k64, int64 *value_ptr);
bool lkx_rb_find_kstr_vdbl(lkx_RB_Tree *tree, lkx_String *key, int64 k64, double *value_ptr);
bool lkx_rb_find_kstr_var(lkx_RB_Tree *tree, lkx_String *key, int64 k64, lkx_Var **value_ptr);
bool lkx_rb_find_kstr_vstr(lkx_RB_Tree *tree, lkx_String *key, int64 k64, lkx_String **value_ptr);

bool lkx_rb_insert_k64_v64(lkx_RB_Tree *tree, int64 key, int64 value);
bool lkx_rb_insert_k64_vdbl(lkx_RB_Tree *tree, int64 key, double value);
bool lkx_rb_insert_k64_var(lkx_RB_Tree *tree, int64 key, lkx_Var *value);
bool lkx_rb_insert_k64_vstr(lkx_RB_Tree *tree, int64 key, lkx_String *value);
bool lkx_rb_insert_kstr_v64(lkx_RB_Tree *tree, lkx_String *key, int64 k64, int64 value);
bool lkx_rb_insert_kstr_vdbl(lkx_RB_Tree *tree, lkx_String *key, int64 k64, double value);
bool lkx_rb_insert_kstr_vstr(lkx_RB_Tree *tree, lkx_String *key, int64 k64, lkx_String *value);
bool lkx_rb_insert_kstr_var(lkx_RB_Tree *tree, lkx_String *key, int64 k64, lkx_Var *value);

#endif
