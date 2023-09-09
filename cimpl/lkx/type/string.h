#ifndef __LKX__TYPE__STRING__
#define __LKX__TYPE__STRING__

#include "lkx/type/base.h"

typedef struct lkx_String {
  uint32 ref_cnt;
  char *data;
  uint32 size;
  uint32 start_idx;
  uint32 length;
} lkx_String;

#endif
