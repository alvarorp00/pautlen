#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "alfa.h"
#include "y.tab.h"

/* Externals values */

/* Input file of Flex */
extern FILE *yyin;

/* Output file of Flex */
extern FILE *yyout;

/* Bison's parser. Returns 0 on OK, 1 on FAILURE */
extern int yyparse(void);

/* Locals */

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

  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure on setup(): %s\n", errbuff);
    return 1;
  }

  if (yyparse())
  {
    fprintf(stderr, "%s.\n", errbuff);
  }
  
  #ifndef _STD_
  
  fclose(yyin);
  fclose(yyout);

  #endif

  return 0;
  
}

/**
 * 
 * Configures basic things for the execution.
 * If _STD_ is specified, will run in manual mode
 */
int setup(int argc, char **argv)
{
  
  line = 1;
  col = 1;

  morfofailure = false;
  
  #ifndef _STD_

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

  yyout = WRITE(argv[2]);
  if(!yyout)
  {
    strcpy(errbuff, "Output file error.\n");
    return 1;
  }

  #else

  yyin = stdin;
  yyout = stdout;

  #endif

  return 0;
}