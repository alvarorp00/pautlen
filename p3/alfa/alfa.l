/* Lexic Analyzer */

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfa.h"
#include "y.tab.h"

#define MAX_LEN 100

#define COPYERR(str, ...) \
            snprintf(errbuff, BUFF, "at alfa.l: *** [at line: %d; col: %d]: "str, line, col, ##__VA_ARGS__);

/* External values */
extern int line;
extern int col;

char errbuff[BUFF];
bool morfofailure;

/* Local method */
int checkIdentifier();

%}
  /* We want to process just one file */
%option noyywrap

  /* To get current line */
%option yylineno

IDENTIFIER [a-zA-Z][0-9a-zA-Z]*
CONSTANT [0-9]+

%%

  /* Reserved words */

main { return TOK_MAIN; }
int { return TOK_INT; }
boolean { return TOK_BOOLEAN; }
array { return TOK_ARRAY; }
function { return TOK_FUNCTION; }
if { return TOK_IF; }
else { return TOK_ELSE; }
while { return TOK_WHILE; }
scanf { return TOK_SCANF; }
printf { return TOK_PRINTF; }
return { return TOK_RETURN; }

  /* Characters */

";" { return yytext[0]; }
"," { return yytext[0]; }
"(" { return yytext[0]; }
")" { return yytext[0]; }
"[" { return yytext[0]; }
"]" { return yytext[0]; }
"{" { return yytext[0]; }
"}" { return yytext[0]; }
"=" { return yytext[0]; }
"+" { return yytext[0]; }
"-" { return yytext[0]; }
"/" { return yytext[0]; }
"*" { return yytext[0]; }
"<" { return yytext[0]; }
">" { return yytext[0]; }

"&&" { return TOK_AND; }
"||" { return TOK_OR; }
"!" { return TOK_NOT; }
"==" { return TOK_IGUAL; }
"!=" { return TOK_DISTINTO; }
"<=" { return TOK_MENORIGUAL; }
">=" { return TOK_MAYORIGUAL; }

  /* Constants */

{CONSTANT} { return TOK_CONSTANTE_ENTERA; }
true { return TOK_TRUE; }
false { return TOK_FALSE; }

  /* Identifiers */

{IDENTIFIER} { return checkIdentifier(); }

 /* Reading Rules */

[ \t\r] { col++; } /* Do nothing on spaces */
\n { line++; col=1; } /* Reset column and update line counter */
"//".*\n { line++; col=1; } /* Same as above, but ignoring comments */

  /* Default option if above don't match -> Error */

. { COPYERR("Unknown symbol %s. ", yytext); morfofailure = 1; return TOK_ERROR; }

%%

int checkIdentifier()
{
  if(yyleng < MAX_LEN)
    return TOK_IDENTIFICADOR;

  morfofailure = true;
  COPYERR("Indentifier length > %d: %s", MAX_LEN, yytext);

  return TOK_ERROR;
}