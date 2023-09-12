#ifndef __LKX__CONTAINER__MAP__
#define __LKX__CONTAINER__MAP__

#include "lkx/container/rbtree.h"

typedef enum lkx_MAP_FUNC {
  FUNC_INSERT_K64_V64,
  FUNC_INSERT_K64_VDBL,
  FUNC_INSERT_K64_VSTR,
  FUNC_INSERT_K64_VMAP,
  FUNC_INSERT_K64_VMMAP,
  FUNC_INSERT_K64_VSET,
  FUNC_INSERT_K64_VARR,
  FUNC_INSERT_K64_VHASH,
  FUNC_INSERT_K64_VIST,
  FUNC_INSERT_K64_VOST,
  FUNC_INSERT_KSTR_V64,
  FUNC_INSERT_KSTR_VDBL,
  FUNC_INSERT_KSTR_VSTR,
  FUNC_INSERT_KSTR_VMAP,
  FUNC_INSERT_KSTR_VMMAP,
  FUNC_INSERT_KSTR_VSET,
  FUNC_INSERT_KSTR_VARR,
  FUNC_INSERT_KSTR_VHASH,
  FUNC_INSERT_KSTR_VIST,
  FUNC_INSERT_KSTR_VOST,
  FUNC_FIND_K64_V64,
  FUNC_FIND_K64_VDBL,
  FUNC_FIND_K64_VSTR,
  FUNC_FIND_K64_VMAP,
  FUNC_FIND_K64_VMMAP,
  FUNC_FIND_K64_VSET,
  FUNC_FIND_K64_VARR,
  FUNC_FIND_K64_VHASH,
  FUNC_FIND_K64_VIST,
  FUNC_FIND_K64_VOST,
  FUNC_FIND_KSTR_V64,
  FUNC_FIND_KSTR_VDBL,
  FUNC_FIND_KSTR_VSTR,
  FUNC_FIND_KSTR_VMAP,
  FUNC_FIND_KSTR_VMMAP,
  FUNC_FIND_KSTR_VSET,
  FUNC_FIND_KSTR_VARR,
  FUNC_FIND_KSTR_VHASH,
  FUNC_FIND_KSTR_VIST,
  FUNC_FIND_KSTR_VOST,
  FUNC_EXIST_K64,
  FUNC_EXIST_KSTR,
  FUNC_ERASE_K64_V64,
  FUNC_ERASE_K64_VDBL,
  FUNC_ERASE_K64_VSTR,
  FUNC_ERASE_K64_VMAP,
  FUNC_ERASE_K64_VMMAP,
  FUNC_ERASE_K64_VSET,
  FUNC_ERASE_K64_VARR,
  FUNC_ERASE_K64_VHASH,
  FUNC_ERASE_K64_VIST,
  FUNC_ERASE_K64_VOST,
  FUNC_ERASE_KSTR_V64,
  FUNC_ERASE_KSTR_VDBL,
  FUNC_ERASE_KSTR_VSTR,
  FUNC_ERASE_KSTR_VMAP,
  FUNC_ERASE_KSTR_VMMAP,
  FUNC_ERASE_KSTR_VSET,
  FUNC_ERASE_KSTR_VARR,
  FUNC_ERASE_KSTR_VHASH,
  FUNC_ERASE_KSTR_VIST,
  FUNC_ERASE_KSTR_VOST,
  FUNC_CLEAR_K64,
  FUNC_CLEAR_K64_VSTR,
  FUNC_CLEAR_K64_VMAP,
  FUNC_CLEAR_K64_VMMAP,
  FUNC_CLEAR_K64_VSET,
  FUNC_CLEAR_K64_VARR,
  FUNC_CLEAR_K64_VHASH,
  FUNC_CLEAR_K64_VIST,
  FUNC_CLEAR_K64_VOST,
  FUNC_CLEAR_KSTR,
  FUNC_CLEAR_KSTR_VSTR,
  FUNC_CLEAR_KSTR_VMAP,
  FUNC_CLEAR_KSTR_VMMAP,
  FUNC_CLEAR_KSTR_VSET,
  FUNC_CLEAR_KSTR_VARR,
  FUNC_CLEAR_KSTR_VHASH,
  FUNC_CLEAR_KSTR_VIST,
  FUNC_CLEAR_KSTR_VOST,
  MAP_FUNC_MAX
} lkx_MAP_FUNC;

typedef struct lkx_Map {
  uint32 ref_cnt;
  lkx_RB_Tree *rbtree;
  lkx_MAP_FUNC clear_func;
} lkx_Map;

typedef struct lkx_RB_Iterator {
  lkx_Map *host;
  lkx_RB_Node *cur;
  lkx_RB_Node *forward;
} lkx_RB_Iterator;

//reverse iterator
typedef struct lkx_RB_RIterator {
  lkx_Map *host;
  lkx_RB_Node *cur;
  lkx_RB_Node *forward;
} lkx_RB_RIterator;

typedef struct lkx_Hub lkx_Hub;
bool (*map_call[MAP_FUNC_MAX])(lkx_Hub *hub, lkx_Map *map);

bool lkx_map_exist_k64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_exist_kstr(lkx_Hub *hub, lkx_Map *map);

bool lkx_map_find_k64_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_k64_vost(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_find_kstr_vost(lkx_Hub *hub, lkx_Map *map);

bool lkx_map_erase_k64_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_k64_vost(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_erase_kstr_vost(lkx_Hub *hub, lkx_Map *map);

bool lkx_map_insert_k64_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_k64_vost(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_v64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vdbl(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_insert_kstr_vost(lkx_Hub *hub, lkx_Map *map);

bool lkx_map_clear_k64(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_k64_vost(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vstr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vset(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vmmap(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_varr(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vhash(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vist(lkx_Hub *hub, lkx_Map *map);
bool lkx_map_clear_kstr_vost(lkx_Hub *hub, lkx_Map *map);

#endif
