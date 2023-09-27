#ifndef __LKX__HUB__
#define __LKX__HUB__

#include "lkx/function.h"

typedef struct lkx_Slot {
  lkx_Var *arr;
  uint32 idx;
  uint32 size;
} lkx_Slot;

typedef struct lkx_Hub {
  lkx_Block *cur_block;
  lkx_Var *var_alive;
  uint32 idx;
  uint32 size;
  char *hub_path;
  bool loaded;

  //register
  lkx_Slot RA;
  lkx_Slot RARG;
} lkx_Hub;

#endif
