#ifndef __LKX__PARSE__
#define __LKX__PARSE__

#include <stdio.h>
#include "lkx/hub.h"

bool parse_hub_file(lkx_Hub *hub, FILE *fp);
bool parse_mod_file(lkx_Hub *hub, FILE *fp);
bool parse_hub_func(lkx_Hub *hub, FILE *fp);
bool parse_mod_func(lkx_Hub *hub, FILE *fp);

#endif
