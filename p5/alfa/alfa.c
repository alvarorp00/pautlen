#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "alfa.h"
#include "symbolsTable.h"
#include "y.tab.h"

/* Externals values */

/* Input file of Flex */
extern FILE *yyin;

/* Output file of Flex */
extern FILE *yyout;

/* Bison's parser. Returns 0 on OK, 1 on FAILURE */
extern int yyparse(SymbolsTable *st);

/* Locals */

/* Where assembly is written */
FILE *fpasm;

/* Common errbuff defined in "alfa.h" */
char errbuff[BUFF];

/* Common flag defined in "alfa.h" */
bool morfofailure;

/* Common line value defined in "alfa.h" */
int line;

/* Common column value defined in "alfa.h" */
int col;

/* Prototypes */

int setup(int argc, char **argv);

/* Main function, runs bison parser */

int main(int argc, char **argv)
{

  SymbolsTable *st;

  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure on setup(): %s\n", errbuff);
    return 1;
  }

  st = symbolsTableInit();
  if(!st)
  {
    TO_STDERR("Error at %s: %d. SymbolsTable init FAILED****", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }

  if (yyparse(st))
  {
    fprintf(stderr, "%s.\n", errbuff);
  }

  fclose(yyin);
  fclose(fpasm);

  symbolsTableClean(st);

  return 0;
  
}

/**
 * 
 * Configures basic things for the execution.
 */
int setup(int argc, char **argv)
{
  
  line = 1;
  col = 1;

  morfofailure = false;

  if(argc < 3)
  {
    strcpy(errbuff, "No enough files received. Exiting...\n");
    return 1;
  }

  yyin = READ(argv[1]);
  if(!yyin)
  {
    strcpy(errbuff, "Input file error.\n");
    return 1;
  }

  fpasm = WRITE(argv[2]);
  if(!fpasm)
  {
    strcpy(errbuff, "Output file error.\n");
    return 1;
  }

  return 0;
}