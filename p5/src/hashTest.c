#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "symbol.h"
#include "hash.h"

#define STR(x) #x

#define LIMIT 100

int main(int argc, char const *argv[])
{
  Hash *hash;
  Symbol **symbols;
  Symbol *__s;
  hash_iterator *iterator;
  iterator_node *__inode;

  size_t i;
  char buff[16];

  symbols = (Symbol**)calloc(LIMIT, sizeof(Symbol*));
  hash = hash_init((Hashcode)symbol_hashcode, (Equals)symbol_equals, (Clean)symbol_delete);

  for(i = 0; i < LIMIT; i++)
  {
    snprintf(buff, 16, "__name__%ld", i);
    symbols[i] = symbol_init(buff, (int)i);
    printf("Started: %s\r", symbol_get_key(symbols[i]));
  }

  printf("\nEncoding...\n\n");

  for(i = 0; i < LIMIT; i++)
  {
    if(!hash_encode(hash, symbols[i]))
    {
      printf("Fatal error in encode");
      exit(EXIT_FAILURE);
    }
    
    printf("hash encode [ %ld ] : OK! --> %s\r", i, symbol_get_key(hash_decode(hash, symbols[i])));
  }

  printf("\n\nDecoding...\n");

  for(i = 0; i < LIMIT; i++)
  {
    if(hash_decode(hash, symbols[i]) == NULL)
    {
      printf("\nfatal error in decode: idx %ld\n", i);
      exit(EXIT_FAILURE);
    }
    printf("hash decode [ %ld ] : OK! --> %s\r", i, symbol_get_key(symbols[i]));
  }

  printf("\n\nIterating...\n");

  iterator = hash_iterate(hash);
  
  if(!iterator)
    exit(EXIT_FAILURE);

  for(__inode = first(iterator); hasNext(__inode); __inode = next(__inode))
  {
    __s = (Symbol*)iter_nodeInfo(__inode);
    printf("Retrieved key: %s\n", symbol_get_key(__s));
  }

  hash_iterate_clean(iterator);

  printf("\n\nEND\n\n");

  free(symbols);
  hash_clean(hash);
  
  return 0;
}
