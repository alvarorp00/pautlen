#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#ifndef _STDIN_
#define _STDIN_
#endif

#define READ(file) fopen(file, "r");
#define WRITE(file) fopen(file, "w");

#define BUFF 128

extern char *yytext;
extern FILE *yyin;
extern FILE *yyout;
extern int yylex(void);

char err[BUFF];


int setup(int argc, char **argv);
void updatetoken(int tok);

int main(int argc, char **argv)
{

  int token;
  Hash *hash;

  #ifndef _STDIN_
  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure: %s\n", err);
    return 1;
  }
  #else
  yyin = stdin;
  yyout = stdout;
  #endif

  for(token = yylex(); token != 0; token = yylex()) /* yylex() returns 0 on EOF */
  {
    fprintf(yyout, "Detected: %s\n", yytext);
  }
  
  fclose(yyin);
  fclose(yyout);

  return 0;
  
}

void updatetoken(int tok)
{
  fprintf(yyout, "TOKEN RECEIVED: %d\n", tok);
}

int setup(int argc, char **argv)
{
  if(argc < 3)
  {
    strcpy(err, "No enough files received. Exiting...\n");
    return 1;
  }

  yyin = READ(argv[1]);
  if(!yyin)
  {
    strcpy(err, "Input file error.\n");
    return 1;
  }

  yyout = WRITE(argv[2]);
  if(!yyout)
  {
    strcpy(err, "Output file error.\n");
    return 1;
  }

  fflush(yyin);
  fflush(yyout);

  return 0;
}
