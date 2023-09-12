#ifndef __LKX__CONTAINER__ARRAY__
#define __LKX__CONTAINER__ARRAY__

#include "lkx/var.h"

typedef struct lkx_Array {
  uint32 idx;
  lkx_Var *data;
  uint32 size;
} lkx_Array;

#endif
