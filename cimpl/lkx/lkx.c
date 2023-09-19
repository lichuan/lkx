#include <stdlib.h>
#include "lkx/lkx.h"

lkx_Hub* lkx_init(char *hub_path)
{
  lkx_Hub *hub = malloc(sizeof(lkx_Hub));
  hub->hub_path = hub_path;
  return hub;
}

bool lkx_load(lkx_Hub *hub)
{
  return true;
}

bool lkx_reload(lkx_Hub *hub)
{
  return true;
}

void lkx_close(lkx_Hub *hub)
{
  free(hub);
}
