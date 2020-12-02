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
    printf("Found!! ::: %s :=: %d\n", symbol_get_key(s), symbol_get_value(s));
  else
    printf("Not Found... :[\n");

  printf("Reinsert:: %s\n", declareGlobal(st, "hola_mundo", 5) ? "OK!" : "ERR");

  s = globalUse(st, "hola_mundo");

  if(s != NULL)
    printf("Found!! ::: %s :=: %d\n", symbol_get_key(s), symbol_get_value(s));
  else
    printf("Not Found... :[\n");

  declareGlobal(st, "my_variable", 10);
  if(st_set_vector_variable(st, "my_variable", INT, GLOBAL, NONE, 3))
    printf("Update ok\n");

  s = globalUse(st, "my_variable");

  if(s != NULL)
    printf("Found!! ::: %s :=: %d @@ %d\n", symbol_get_key(s), symbol_get_value(s), symbol_get_category(s));
  else
    printf("Not Found... :[\n");

  symbolsTableClean(st);
  
  return 0;
}
