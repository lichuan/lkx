#include <stdio.h>
#include <stdlib.h>
#include "lkx/lkx.h"

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    printf("You must specify a hub file to run.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
