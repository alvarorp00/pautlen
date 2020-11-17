%{

#include <stdio.h>
#include <stdlib.h>

%}
%option noyywrap

%%

INICIO { printf("reconocido INICIO\n"); }
FIN { printf("reconocido FIN\n"); }
VECTOR { printf("reconocido VECTOR\n"); }
ENTERO { printf("reconocido ENTERO\n"); }
LOGICO { printf("reconocido LOGICO\n"); }
MAIN { printf("{ body_instructions }"); }
"\\" { printf("READ\n"); }

%%

int main(int argc, char **argv)
{

  if(argc == 1)
  {
    printf("No file received. Exiting...\n");
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if(!yyin)
  {
    printf("File error.\n");
    return 1;
  }

  yylex();
  fclose(yyin);

  return 0;
}
