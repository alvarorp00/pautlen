#include <stdio.h>
#include <unistd.h>
#include "symbolsTable.h"

int main(int argc, char const *argv[])
{

  SymbolsTable *st;

  st = symbolsTableInit();

  printf("INIT:: %s\n", st == NULL ? "ERROR" : "OK");

  declareGlobal(st, "hola_mundo", 1);

  Symbol *s = globalUse(st, "hola_mundo");

  if(s != NULL)
    printf("Found!!\n");

  symbolsTableClean(st);
  
  return 0;
}
