#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _STDIN_
#define _STDIN_
#endif

#define BUFF 128

extern FILE *yyin;
extern FILE *yyout;
extern int yylex(void);

char err[BUFF];

int setup(int argc, char **argv);

int main(int argc, char **argv)
{

  int token;

  #ifndef _STDIN_
  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure: %s\n", err);
    return 1;
  }
  #endif

  while((token = yylex()) != 0) /* yylex() returns 0 on EOF */
  {

  }
  
  fclose(yyin);
  fclose(yyout);

  return 0;
  
}

int setup(int argc, char **argv)
{
  if(argc < 3)
  {
    strcpy(err, "No enough files received. Exiting...\n");
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if(!yyin)
  {
    strcpy(err, "Input file error.\n");
    return 1;
  }

  yyout = fopen(argv[2], "w");
  if(!yyout)
  {
    strcpy(err, "Output file error.\n");
    return 1;
  }

  fflush(yyin);
  fflush(yyout);

  return 0;
}
