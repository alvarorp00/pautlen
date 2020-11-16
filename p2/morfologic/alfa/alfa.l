/* Lexic Analyzer */

%{

#include <stdio.h>

%}
%option noyywrap

%%

INICIO { fprintf(yyout, "reconocido INICIO\n"); }
FIN { fprintf(yyout, "reconocido FIN\n"); }
VECTOR { fprintf(yyout, "reconocido VECTOR\n"); }
ENTERO { fprintf(yyout, "reconocido ENTERO\n"); }
LOGICO { fprintf(yyout, "reconocido LOGICO\n"); }
MAIN { fprintf(yyout, "{ body_instructions }\n"); }
"\\" { fprintf(yyout, "READ\n"); }

%%

int main(int argc, char **argv)
{

  if(argc < 3)
  {
    printf("No enough files received. Exiting...\n");
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if(!yyin)
  {
    printf("Input file error.\n");
    return 1;
  }

  yyout = fopen(argv[2], "w");
  if(!yyout)
  {
    printf("Output file error.\n");
    return 1;
  }

  fflush(yyin);
  fflush(yyout);

  yylex();
  
  fclose(yyin);
  fclose(yyout);

  return 0;
  
}