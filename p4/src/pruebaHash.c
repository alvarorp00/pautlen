#include <stdio.h>
#include <unistd.h>
#include "symbolsTable.h"

int main(int argc, char const *argv[])
{

  SymbolsTable *symbolsTable;

  symbolsTable = symbolsTableInit();

  printf("INIT:: %s\n", symbolsTable == NULL ? "ERROR" : "OK");

  symbolsTableClean(symbolsTable);

  Symbol *s, *ret;

  s = symbol_init(VAR, "hola_mundo");

  Hash *hash;

  hash = hash_init((Hashcode)symbol_hashcode, (Equals)symbol_equals, (Clean)symbol_delete);

  hash_encode(hash, s);

  printf("Hash contains ::::: %s\n", hash_contains(hash, s) ? "True" : "False");

  ret = (Symbol*)hash_decode(hash, "hola_mundo");

  fprintf(stdout, "Retval: %s.\n", symbol_get_key(ret));

  printf("Starting LOOP::: \n");

  char name[20];

  for (size_t i = 0; i < 1000; i++)
  {
    sprintf(name, "Henlo_fren%ld", i);
    s = symbol_init(VAR, name);
    hash_encode(hash, s);
    s = hash_decode(hash, s);
    fprintf(stdout, "\t\tRetval: %s.\n", symbol_get_key(s));
  }
  
  printf("\n\n\nDELETE TEST::: \n\n\n");
  sleep(2);

  // for (size_t i = 0; i < 1000; i++)
  // {
  //   sprintf(name, "Henlo_fren%ld", i);
  //   hash_deleteValue(hash, s);
  //   // fprintf(stdout, "\t\tRetval: %s.\n", s == NULL ? "OKKK!" : "ERR");
  // }

  hash_clean(hash);
  
  return 0;
}
