%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
%}
%option noyywrap


%%
TOK { printf("TOKEN DETECTED\n"); }
%%

int main()
{
  return yylex();
}