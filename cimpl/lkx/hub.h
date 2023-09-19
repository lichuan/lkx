#ifndef __LKX__HUB__
#define __LKX__HUB__

#include "lkx/function.h"

typedef struct lkx_Hub {
  lkx_Block *cur_block;
  lkx_Var *var_alive;
  uint32 idx;
  uint32 size;
  char *hub_path;

  //register
  int64 RA;
  int64 RB;
} lkx_Hub;

#endif
