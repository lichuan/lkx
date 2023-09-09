#ifndef __LKX__FUNCTION__
#define __LKX__FUNCTION__

#include "lkx/var.h"

typedef struct lkx_Block {
  struct lkx_Block *parent;
  lkx_Var *block_var;
  uint32 var_size;
  uint32 var_idx;
} lkx_Block;

#endif
