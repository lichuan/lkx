#ifndef __LKX__PARSE__
#define __LKX__PARSE__

#include <stdio.h>
#include "lkx/hub.h"

#define READ_SZ 16*1024

typedef struct lkx_Rbuf {
  int32 size;
  int32 idx;
  char buf[READ_SZ];
} lkx_Rbuf;

bool parse_hub_file(lkx_Hub *hub, FILE *fp);
int32 parse_struct_decl(lkx_Hub *hub, FILE *fp, lkx_Rbuf *rbuf, char *modname, int32 line_num);
bool parse_func_decl(lkx_Hub *hub, FILE *fp);
bool parse_struct_def(lkx_Hub *hub, FILE *fp);
bool parse_func_def(lkx_Hub *hub, FILE *fp);

#endif
