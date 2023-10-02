#include <stdlib.h>
#include <stdio.h>
#include "lkx/lkx.h"
#include "lkx/parse.h"

lkx_Hub* lkx_init(char *hub_path)
{
  lkx_Hub *hub = calloc(1, sizeof(lkx_Hub));
  hub->hub_path = hub_path;
  return hub;
}

bool lkx_load(lkx_Hub *hub)
{
  if(hub->loaded)
  {
    return false;
  }

  FILE *fp = fopen(hub->hub_path, "r");

  if(fp == NULL)
  {
    return false;
  }

  if(!parse_hub_file(hub, fp))
  {
    fclose(fp);
    return false;
  }
  
  fclose(fp);
  hub->loaded = true;
  return true;
}

bool lkx_reload(lkx_Hub *hub)
{
  FILE *fp = fopen(hub->hub_path, "r");

  if(fp == NULL)
  {
    return false;
  }

  if(!parse_hub_file(hub, fp))
  {
    fclose(fp);
    return false;
  }
  
  fclose(fp);
  return true;
}

void lkx_close(lkx_Hub *hub)
{
  free(hub);
}
