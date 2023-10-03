#ifndef __LKX__TYPE__STRING__
#define __LKX__TYPE__STRING__

#include "lkx/type/base.h"

char ascii_map[128];

typedef struct lkx_String {
  uint32 ref_cnt;
  char *data;
  uint32 size;
  uint32 start_idx;
  uint32 length;
  uint64 hash_id1;
  uint64 hash_id2;
} lkx_String;

uint64 identifier_hash_id(char *data, uint32 length);
void lkx_free_str(lkx_String *str);

#endif
