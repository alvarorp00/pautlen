#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main(int argc, char const *argv[])
{
  Hash *hash;

  hash = hash_init(_USE_DEFAULT);

  printf("%s\n", hash_encode(hash, 18, "First attemp") ? "True":"False");
  printf("%s\n", hash_encode(hash, 18, "new val") ? "True":"False");

  printf("%s\n", hash_retrieve(hash, 18));
  printf("%s\n", hash_retrieve(hash, 19));

  hash_remove(hash, 18);
  printf("Retrieved: %s\n", hash_retrieve(hash, 18));
  
  printf("%s\n", hash_encode(hash, 18, "new val") ? "True":"False");
  printf("Retrieved: %s\n", hash_retrieve(hash, 18));
  
  return 0;
}
