#ifndef __LKX__CONTAINER__MAP__
#define __LKX__CONTAINER__MAP__

#include "lkx/container/rbtree.h"

typedef enum lkx_Map_FUNC {
  FUNC_INSERT_K64_V64,
  FUNC_INSERT_K64_VDBL,
  FUNC_INSERT_K64_VSTR,
  FUNC_INSERT_K64_VMAP,
  FUNC_INSERT_K64_VSET,
  FUNC_INSERT_K64_VARR,
  FUNC_INSERT_K64_VHASH,
  FUNC_INSERT_K64_VIST,
  FUNC_INSERT_K64_VOST,


  
} lkx_Map_FUNC;

typedef struct lkx_RB_Iterator {
  lkx_RB_Node *cur;
  lkx_RB_Node *forward;
} lkx_RB_Iterator;

//reverse iterator
typedef struct lkx_RB_RIterator {
  lkx_RB_Node *cur;
  lkx_RB_Node *forward;
} lkx_RB_RIterator;

typedef struct lkx_Map {
  uint32 ref_cnt;
  lkx_RB_Tree *rbtree;
} lkx_Map;

typedef struct lkx_Hub lkx_Hub;

bool call_map_func(lkx_Map *map, lkx_Hub *hub);

#endif
