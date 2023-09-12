#include "lkx/type/string.h"

char ascii_map[128] = {
  ['A']=1, ['B']=2, ['C']=3, ['D']=4, ['E']=5, ['F']=6, ['G']=7, ['H']=8, ['I']=9, ['J']=10, ['K']=11, ['L']=12, ['M']=13, ['N']=14, ['O']=15, ['P']=16, ['Q']=17, ['R']=18, ['S']=19, ['T']=20, ['U']=21, ['V']=22, ['W']=23, ['X']=24, ['Y']=25, ['Z']=26, ['_']=27, ['a']=28, ['b']=29, ['c']=30, ['d']=31, ['e']=32, ['f']=33, ['g']=34, ['h']=35, ['i']=36, ['j']=37, ['k']=38, ['l']=39, ['m']=40, ['n']=41, ['o']=42, ['p']=43, ['q']=44, ['r']=45, ['s']=46, ['t']=47, ['u']=48, ['v']=49, ['w']=50, ['x']=51, ['y']=52, ['z']=53
};

uint64 identifier_hash_id(char *data, uint32 length)
{
  if(length == 0) {
    return 0;
  }
  
  uint64 hash_id = 0;
  
  if(length < 11) {
    int i = 0;
    for(; i < length; ++i) {
      hash_id = ascii_map[data[i]] + hash_id * 53;
    }
    
    while(i++ < 11) {
      hash_id *= 53;
    }

    return hash_id;
  }

  for(int i = 0; i < 11; ++i) {
    hash_id = ascii_map[data[i]] + hash_id * 53;
  }

  return hash_id;
}
