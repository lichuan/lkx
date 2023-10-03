#ifndef __LKX__CONTAINER__RBTREE1__
#define __LKX__CONTAINER__RBTREE1__

#include "lkx/type/string.h"
#include "lkx/var.h"
#include "lkx/container/base.h"

// for set
typedef struct lkx_RB_Node1 {
  lkx_RB_COLOR color;
  struct lkx_RB_Node1 *left;
  struct lkx_RB_Node1 *right;
  struct lkx_RB_Node1 *parent;
  
  union {
    int64 k64;
    lkx_String *kstr;
  };
} lkx_RB_Node1;

// for set
typedef struct lkx_RB_Tree1 {
  lkx_RB_Node1 *root;
} lkx_RB_Tree1;

bool lkx_rb_1_exist_k64(lkx_RB_Tree1 *tree, int64 key);
bool lkx_rb_1_exist_kstr(lkx_RB_Tree1 *tree, lkx_String *key);
bool lkx_rb_1_insert_k64(lkx_RB_Tree1 *tree, int64 key);
bool lkx_rb_1_insert_kstr(lkx_RB_Tree1 *tree, lkx_String *key);
bool lkx_rb_1_erase_k64(lkx_RB_Tree1 *tree, int64 key);
bool lkx_rb_1_erase_kstr(lkx_RB_Tree1 *tree, lkx_String *key);
void lkx_free_node1(lkx_RB_Node1 *node);

#endif
