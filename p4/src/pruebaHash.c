#include <stdio.h>
#include <unistd.h>
#include "symbolsTable.h"

#define NEGATIVE_N SCHAR_MIN /* For negative numbers used here */
#define POSITIVE_N SCHAR_MAX /* For positive numbers used here */

#define PRINT_RESPONSE(response, name, mode) \
            TO_STDOUT("-->%s of %s<--- %s", mode, name, response == true ? "Success" : "Failure")

void do_test();
void selfTest();

String modes[4] = {"Insertion", "Search", "Scope Opening", "Scope Closing"};

int main(int argc, char const *argv[])
{

  do_test();
  
  return 0;
}

/* ------- TESTS -------- */

void do_test()
{
  SymbolsTable *st;
  Symbol *s;
  bool response;

  // Initialise SymbolsTable
  st = symbolsTableInit();
  // Global scope is now opened

  // Insert [uno: 1]
  response = declareGlobal(st, "uno", 1);
  PRINT_RESPONSE(response, "uno", modes[0]);

  // Insert [dos: 2]
  response = declareGlobal(st, "dos", 2);
  PRINT_RESPONSE(response, "dos", modes[0]);
  
  symbolsTableClean(st); // Clean resources
}

/* ------- OTHER -------- */

void selfTest()
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
}