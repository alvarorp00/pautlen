#include <stdio.h>
#include "symbolsTable.h"
#include "hash.h"

int main(int argc, char const *argv[])
{

  SymbolsTable *symbolsTable;

  symbolsTable = symbolsTableInit();

  symbolsTableClean(symbolsTable);

  Hash *hash;

  hash = hash_init();

  if(!hash)
    fprintf(stdout, "ERROR INIT_HASH\n");

  bool ret = hash_encode(hash, "hola_mundo");

  fprintf(stdout, "Insertion: %s.\n", ret ? "True" : "False");

  fprintf(stdout, "Return: %s.\n", hash_decode(hash, "hola_mundo") == NULL ? "ERROR" : "OK!");

  hash_clean(hash);
  
  return 0;
}
