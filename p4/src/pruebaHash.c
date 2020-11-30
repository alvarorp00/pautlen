#include <stdio.h>
#include "symbolsTable.h"

int main(int argc, char const *argv[])
{

  SymbolsTable *symbolsTable;

  symbolsTable = symbolsTableInit();

  printf("INIT:: %s\n", symbolsTable == NULL ? "ERROR" : "OK");

  symbolsTableClean(symbolsTable);

  SymbolNode *sn;

  sn = node_init(VAR, "hola_mundo");

  Hash *hash;

  hash = hash_init();

  hash_encode(hash, sn);

  SymbolNode *ret;

  ret = hash_decode(hash, "hola_mundo");

  fprintf(stdout, "Retval: %s.\n", node_get_key(ret));

  hash_clean(hash);
  
  return 0;
}
