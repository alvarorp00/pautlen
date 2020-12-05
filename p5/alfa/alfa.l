/* Lexic Analyzer */

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "alfa.h"
#include "y.tab.h"

/* Maximum length for Identifiers */
#define MAX_LEN 100

/* Prints token in default flex output */
#define PRINT_TOK(str) fprintf(yyout, ";D:\t%s\n", str);

/* Common line value defined in "alfa.h" */
int line;

/* Common column value defined in "alfa.h" */
int col;

/* Common errbuff defined in "alfa.h" */
char errbuff[BUFF];

/* Common morfologic failure flag def in "alfa.h" */
bool morfofailure;

/* Local method */
int checkIdentifier();
void unknownSymbol();
void processToken();

%}
  /* We want to process just one file */
%option noyywrap

  /* To get current line */
%option yylineno

IDENTIFIER [a-zA-Z][0-9a-zA-Z]*
CONSTANT [0-9]+

%%

  /* Reserved words */

main { processToken(); return TOK_MAIN; }
int { processToken(); return TOK_INT; }
boolean { processToken(); return TOK_BOOLEAN; }
array { processToken(); return TOK_ARRAY; }
function { processToken(); return TOK_FUNCTION; }
if { processToken(); return TOK_IF; }
else { processToken(); return TOK_ELSE; }
while { processToken(); return TOK_WHILE; }
scanf { processToken(); return TOK_SCANF; }
printf { processToken(); return TOK_PRINTF; }
return { processToken(); return TOK_RETURN; }

  /* Characters */

";" { processToken(); return TOK_PUNTOYCOMA; }
"," { processToken(); return TOK_COMA; }
"(" { processToken(); return TOK_PARENTESISIZQUIERDO; }
")" { processToken(); return TOK_PARENTESISDERECHO; }
"[" { processToken(); return TOK_CORCHETEIZQUIERDO; }
"]" { processToken(); return TOK_CORCHETEDERECHO; }
"{" { processToken(); return TOK_LLAVEIZQUIERDA; }
"}" { processToken(); return TOK_LLAVEDERECHA; }
"=" { processToken(); return TOK_ASIGNACION; }
"+" { processToken(); return TOK_MAS; }
"-" { processToken(); return TOK_MENOS; }
"*" { processToken(); return TOK_ASTERISCO; }
"/" { processToken(); return TOK_DIVISION; }
"<" { processToken(); return TOK_MENOR; }
">" { processToken(); return TOK_MAYOR; }

"&&" { processToken(); return TOK_AND; }
"||" { processToken(); return TOK_OR; }
"!" { processToken(); return TOK_NOT; }
"==" { processToken(); return TOK_IGUAL; }
"!=" { processToken(); return TOK_DISTINTO; }
"<=" { processToken(); return TOK_MENORIGUAL; }
">=" { processToken(); return TOK_MAYORIGUAL; }

  /* Constants */

{CONSTANT} { processToken(); return TOK_CONSTANTE_ENTERA; }
true { processToken(); return TOK_TRUE; }
false { processToken(); return TOK_FALSE; }

  /* Identifiers */

{IDENTIFIER} { return checkIdentifier(); }

 /* Reading Rules */

[ \t\r] { col++; } /* Do nothing on spaces */
\n { line++; col=1; } /* Reset column and update line counter */
"//".*\n { line++; col=1; } /* Same as above, but ignoring comments */

  /* Default option if above don't match -> Error */

. { unknownSymbol(); return TOK_ERROR; }

%%

/* Checks if identifier read is valid and manages situation */
int checkIdentifier()
{
  
  if(yyleng < MAX_LEN)
  {
    processToken();
    return TOK_IDENTIFICADOR;
  }

  morfofailure = true;
  COPYERR("alfa.l", "Indentifier length > %d: %s", MAX_LEN, yytext);
  return TOK_ERROR;

}

/* Process response on morfologic failure */
void unknownSymbol()
{
  COPYERR("alfa.l", "Unknown symbol %s. ", yytext);
  morfofailure = true;
}

/* Do default action for each token identified by yylex() */
void processToken()
{
  col += yyleng;
  
  PRINT_TOK(yytext);
}