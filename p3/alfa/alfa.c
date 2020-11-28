#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "y.tab.h"
#include "alfa.h"

/* Externals */

extern int yyleng;
extern char *yytext;
extern FILE *yyin;
extern FILE *yyout;

extern int yylex(void);
extern int yyparse(void);

/* Locals */

char errbuff[BUFF];
bool morfofailure;

int line;
int col;

int setup(int argc, char **argv);
int processToken(int tok);
// void selectToken(int tok, char *tok_exp);

int main(int argc, char **argv)
{

  int token;

  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure on setup(): %s\n", errbuff);
    return 1;
  }

  yyparse();
  
  
  #ifndef _STD_
  
  fclose(yyin);
  fclose(yyout);

  #endif

  return 0;
  
}


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