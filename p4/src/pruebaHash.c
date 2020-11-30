#include <stdio.h>
#include "symbolsTable.h"

int main(int argc, char const *argv[])
{

  SymbolsTable *symbolsTable;

  symbolsTable = symbolsTableInit();

  printf("INIT:: %s\n", symbolsTable == NULL ? "ERROR" : "OK");

  symbolsTableClean(symbolsTable);
  
  return 0;
}
