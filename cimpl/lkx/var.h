#ifndef __LKX__VAR__
#define __LKX__VAR__

#include "lkx/type/base.h"

typedef enum lkx_VAR_TYPE {
  VAR_TYPE_I64,
  VAR_TYPE_DBL,
  VAR_TYPE_BOOL,
  VAR_TYPE_STR,
  VAR_TYPE_ARR,
  VAR_TYPE_MAP,
  VAR_TYPE_MMAP,
  VAR_TYPE_SET,
  VAR_TYPE_HASH,
  VAR_TYPE_IST,
  VAR_TYPE_OST,
} lkx_VAR_TYPE;

typedef struct lkx_Var {
  lkx_VAR_TYPE type;
  union {
    int64 i64;
    double dbl;
    struct lkx_String *str;
    struct lkx_Array *arr;
    struct lkx_Map *map;
    struct lkx_M_Map *mmap;
    struct lkx_Set *set;
    struct lkx_Hash *hash;
    struct lkx_IStruct *ist;
    struct lkx_OStruct *ost;
  };
} lkx_Var;

#endif
