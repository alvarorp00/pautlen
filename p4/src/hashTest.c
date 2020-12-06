#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "symbol.h"
#include "hash.h"

#define STR(x) #x

#define LIMIT 800000

int main(int argc, char const *argv[])
{
  Hash *hash;
  Symbol *symbols[LIMIT];
  size_t i;
  char buff[16];

  hash = hash_init((Hashcode)symbol_hashcode, (Equals)symbol_equals, (Clean)symbol_delete);

  for(i = 0; i < LIMIT; i++)
  {
    snprintf(buff, 16, "__name__%ld", i);
    symbols[i] = symbol_init(buff, (int)i);
    // usleep(100000);
    printf("Started: %s\n", symbol_get_key(symbols[i]));
  }

  printf("\nEncoding...\n\n");

  for(i = 0; i < LIMIT; i++)
  {
    if(!hash_encode(hash, symbols[i]))
    {   
      printf("Fatal error in encode");
      exit(EXIT_FAILURE);
    }
    printf("hash encode [ %ld ] : OK! --> %s\n", i, symbol_get_key(symbols[i]));
    // usleep(100000);
  }

  printf("\n\nDecoding...\n");

  for(i = 0; i < LIMIT; i++)
  {
    if(hash_decode(hash, symbols[i]) == NULL)
    {
      printf("\nfatal error in decode: idx %ld\n", i);
      exit(EXIT_FAILURE);
    }
    printf("hash decode [ %ld ] : OK! --> %s\n", i, symbol_get_key(symbols[i]));
  }

  hash_clean(hash);
  
  return 0;
}
