#ifndef __LKX__HUB__
#define __LKX__HUB__

#include "lkx/function.h"

typedef struct lkx_Hub {
  lkx_Block *cur_block;
  lkx_Var *var_alive;
  uint32 var_idx;
  uint32 var_size;
} lkx_Hub;

#endif
