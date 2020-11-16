/* Lexic Analyzer */

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define UPDATE_COL col++

#define MAX_LEN 100
#define BUFF 128

static int col = 0;
char err[BUFF];

int setup(int argc, char **argv);

%}
%option noyywrap

IDENTIFIER [a-zA-Z][a-zA-Z]*

%%

"main"
"array"
"int"
"if"
"else"
"while"

IDENTIFIER { if(strlen(yytext)>MAX_LEN); }

%%
