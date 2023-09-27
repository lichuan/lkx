#include <stdio.h>
#include <stdlib.h>
#include "lkx/type/string.h"
#include "lkx/lkx.h"

int main()
{
  printf("Hello the lkx language.\n");
  lkx_Hub *hub = lkx_init("script/lkxsample/hub.lkx");

  if(!lkx_load(hub))
  {
    printf("lkx_load failed!\n");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
