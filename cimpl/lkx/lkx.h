#ifndef __LKX__LKX__
#define __LKX__LKX__

#include "lkx/hub.h"

lkx_Hub* lkx_init(char *hub_path);
bool lkx_load(lkx_Hub *hub);
bool lkx_reload(lkx_Hub *hub);
void lkx_close(lkx_Hub *hub);

#endif
