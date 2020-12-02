#include <stdio.h>
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

  hash_clean(hash);
  
  return 0;
}
