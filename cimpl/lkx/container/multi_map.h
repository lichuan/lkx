#ifndef __LKX__CONTAINER__MULTI_MAP__
#define __LKX__CONTAINER__MULTI_MAP__

#include "lkx/container/rbtree.h"

typedef enum lkx_M_MAP_FUNC {
  FUNC_M_INSERT_K64_V64,
  FUNC_M_INSERT_K64_VDBL,
  FUNC_M_INSERT_K64_VSTR,
  FUNC_M_INSERT_K64_VMAP,
  FUNC_M_INSERT_K64_VMMAP,
  FUNC_M_INSERT_K64_VSET,
  FUNC_M_INSERT_K64_VARR,
  FUNC_M_INSERT_K64_VHASH,
  FUNC_M_INSERT_K64_VIST,
  FUNC_M_INSERT_K64_VOST,
  FUNC_M_INSERT_KSTR_V64,
  FUNC_M_INSERT_KSTR_VDBL,
  FUNC_M_INSERT_KSTR_VSTR,
  FUNC_M_INSERT_KSTR_VMAP,
  FUNC_M_INSERT_KSTR_VMMAP,
  FUNC_M_INSERT_KSTR_VSET,
  FUNC_M_INSERT_KSTR_VARR,
  FUNC_M_INSERT_KSTR_VHASH,
  FUNC_M_INSERT_KSTR_VIST,
  FUNC_M_INSERT_KSTR_VOST,
  FUNC_M_FIND_K64_V64,
  FUNC_M_FIND_K64_VDBL,
  FUNC_M_FIND_K64_VSTR,
  FUNC_M_FIND_K64_VMAP,
  FUNC_M_FIND_K64_VMMAP,
  FUNC_M_FIND_K64_VSET,
  FUNC_M_FIND_K64_VARR,
  FUNC_M_FIND_K64_VHASH,
  FUNC_M_FIND_K64_VIST,
  FUNC_M_FIND_K64_VOST,
  FUNC_M_FIND_KSTR_V64,
  FUNC_M_FIND_KSTR_VDBL,
  FUNC_M_FIND_KSTR_VSTR,
  FUNC_M_FIND_KSTR_VMAP,
  FUNC_M_FIND_KSTR_VMMAP,
  FUNC_M_FIND_KSTR_VSET,
  FUNC_M_FIND_KSTR_VARR,
  FUNC_M_FIND_KSTR_VHASH,
  FUNC_M_FIND_KSTR_VIST,
  FUNC_M_FIND_KSTR_VOST,
  FUNC_M_EXIST_K64,
  FUNC_M_EXIST_KSTR,
  FUNC_M_ERASE_K64_V64,
  FUNC_M_ERASE_K64_VDBL,
  FUNC_M_ERASE_K64_VSTR,
  FUNC_M_ERASE_K64_VMAP,
  FUNC_M_ERASE_K64_VMMAP,
  FUNC_M_ERASE_K64_VSET,
  FUNC_M_ERASE_K64_VARR,
  FUNC_M_ERASE_K64_VHASH,
  FUNC_M_ERASE_K64_VIST,
  FUNC_M_ERASE_K64_VOST,
  FUNC_M_ERASE_KSTR_V64,
  FUNC_M_ERASE_KSTR_VDBL,
  FUNC_M_ERASE_KSTR_VSTR,
  FUNC_M_ERASE_KSTR_VMAP,
  FUNC_M_ERASE_KSTR_VMMAP,
  FUNC_M_ERASE_KSTR_VSET,
  FUNC_M_ERASE_KSTR_VARR,
  FUNC_M_ERASE_KSTR_VHASH,
  FUNC_M_ERASE_KSTR_VIST,
  FUNC_M_ERASE_KSTR_VOST,
  FUNC_M_CLEAR_K64,
  FUNC_M_CLEAR_K64_VSTR,
  FUNC_M_CLEAR_K64_VMAP,
  FUNC_M_CLEAR_K64_VMMAP,
  FUNC_M_CLEAR_K64_VSET,
  FUNC_M_CLEAR_K64_VARR,
  FUNC_M_CLEAR_K64_VHASH,
  FUNC_M_CLEAR_K64_VIST,
  FUNC_M_CLEAR_K64_VOST,
  FUNC_M_CLEAR_KSTR,
  FUNC_M_CLEAR_KSTR_VSTR,
  FUNC_M_CLEAR_KSTR_VMAP,
  FUNC_M_CLEAR_KSTR_VMMAP,
  FUNC_M_CLEAR_KSTR_VSET,
  FUNC_M_CLEAR_KSTR_VARR,
  FUNC_M_CLEAR_KSTR_VHASH,
  FUNC_M_CLEAR_KSTR_VIST,
  FUNC_M_CLEAR_KSTR_VOST,
  M_MAP_FUNC_MAX
} lkx_M_MAP_FUNC;

typedef struct lkx_M_Map {
  uint32 ref_cnt;
  lkx_RB_M_Tree *rbtree;
  lkx_M_MAP_FUNC clear_func;
} lkx_M_Map;

typedef struct lkx_RB_M_Iterator {
  lkx_M_Map *host;
  lkx_RB_M_Node *cur;
  lkx_RB_M_Node *forward;
} lkx_RB_M_Iterator;

//reverse iterator
typedef struct lkx_RB_M_RIterator {
  lkx_M_Map *host;
  lkx_RB_M_Node *cur;
  lkx_RB_M_Node *forward;
} lkx_RB_M_RIterator;

typedef struct lkx_Hub lkx_Hub;
bool (*m_map_call[M_MAP_FUNC_MAX])(lkx_Hub *hub, lkx_M_Map *map);

bool lkx_map_exist_k64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_exist_kstr(lkx_Hub *hub, lkx_M_Map *map);

bool lkx_map_find_k64_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_k64_vost(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_find_kstr_vost(lkx_Hub *hub, lkx_M_Map *map);

bool lkx_map_erase_k64_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_k64_vost(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_erase_kstr_vost(lkx_Hub *hub, lkx_M_Map *map);

bool lkx_map_insert_k64_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_k64_vost(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_v64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vdbl(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_insert_kstr_vost(lkx_Hub *hub, lkx_M_Map *map);

bool lkx_map_clear_k64(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_k64_vost(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vstr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vset(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vmmap(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_varr(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vhash(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vist(lkx_Hub *hub, lkx_M_Map *map);
bool lkx_map_clear_kstr_vost(lkx_Hub *hub, lkx_M_Map *map);

#endif
