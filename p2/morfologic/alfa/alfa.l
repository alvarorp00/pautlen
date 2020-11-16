/* Lexic Analyzer */

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define BYTES
#define MAX_LEN 100

#define UPDATECOL col++
#define TOKEN(x) updatetoken(x)

static int col = 0;

extern void updatetoken(int tok);

%}
%option noyywrap

IDENTIFIER [a-zA-Z][a-zA-Z]*

%%

"main" { UPDATECOL; TOKEN(TOK_MAIN); return TOK_MAIN; }
"array" { UPDATECOL; TOKEN(TOK_ARRAY); return TOK_ARRAY; }
"int" { UPDATECOL; TOKEN(TOK_INT); return TOK_INT; }
"if" { UPDATECOL; TOKEN(TOK_IF); return TOK_IF; }
"else" { UPDATECOL; TOKEN(TOK_ELSE); return TOK_ELSE; }
"while" { UPDATECOL; TOKEN(TOK_WHILE); return TOK_WHILE; }

%%
