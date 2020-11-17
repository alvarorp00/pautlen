#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "alfa.h"

// #ifndef _STD_
// #define _STD_
// #endif

/* Externals */

extern char *yytext;
extern FILE *yyin;
extern FILE *yyout;

extern int yylex(void);

/* Locals */

char errbuff[BUFF];

int line;
int col;

int setup(int argc, char **argv);
int processToken(int tok);
void selectToken(int tok, char *tok_exp);

int main(int argc, char **argv)
{

  int token;

  if(setup(argc, argv))
  {
    fprintf(stderr, "Failure on setup(): %s\n", errbuff);
    return 1;
  }

  for(token = yylex(); token != 0; token = yylex()) /* yylex() returns 0 on EOF */
  {
    if(processToken(token) == TOK_ERROR)
      break;
  }
  
  #ifndef _STD_
  
  fclose(yyin);
  fclose(yyout);

  #endif

  return 0;
  
}


int processToken(int tok)
{
  char tok_exp[BUFF];
  
  col++;
  
  if (tok == TOK_ERROR)
  {
    fprintf(stderr, "\tFAILURE. %s\n", errbuff);
    return tok;
  }

  selectToken(tok, tok_exp);
  
  fprintf(yyout, "%s %d %s\n", tok_exp, tok, yytext);

  return tok;
}


int setup(int argc, char **argv)
{
  
  line = 1;
  col = 1;
  
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

  fflush(yyin);
  fflush(yyout);

  return 0;
}


void selectToken(int tok, char *tok_exp)
{
  switch (tok)
  {
  case TOK_MAIN:
    strncpy(tok_exp, STRINGIFY(TOK_MAIN), BUFF);
    break;
  
  case TOK_INT:
    strncpy(tok_exp, STRINGIFY(TOK_INT), BUFF);
    break;

  case TOK_BOOLEAN:
    strncpy(tok_exp, STRINGIFY(TOK_BOOLEAN), BUFF);
    break;
  
  case TOK_ARRAY:
    strncpy(tok_exp, STRINGIFY(TOK_ARRAY), BUFF);
    break;

  case TOK_FUNCTION:
    strncpy(tok_exp, STRINGIFY(TOK_FUNCTION), BUFF);
    break;
  
  case TOK_IF:
    strncpy(tok_exp, STRINGIFY(TOK_IF), BUFF);
    break;

  case TOK_ELSE:
    strncpy(tok_exp, STRINGIFY(TOK_ELSE), BUFF);
    break;
  
  case TOK_WHILE:
    strncpy(tok_exp, STRINGIFY(TOK_WHILE), BUFF);
    break;

  case TOK_SCANF:
    strncpy(tok_exp, STRINGIFY(TOK_SCANF), BUFF);
    break;
  
  case TOK_PRINTF:
    strncpy(tok_exp, STRINGIFY(TOK_PRINTF), BUFF);
    break;

  case TOK_PUNTOYCOMA:
    strncpy(tok_exp, STRINGIFY(TOK_PUNTOYCOMA), BUFF);
    break;
  
  case TOK_RETURN:
    strncpy(tok_exp, STRINGIFY(TOK_RETURN), BUFF);
    break;

  case TOK_COMA:
    strncpy(tok_exp, STRINGIFY(TOK_COMA), BUFF);
    break;
  
  case TOK_PARENTESISIZQUIERDO:
    strncpy(tok_exp, STRINGIFY(TOK_PARENTESISIZQUIERDO), BUFF);
    break;

  case TOK_PARENTESISDERECHO:
    strncpy(tok_exp, STRINGIFY(TOK_PARENTESISDERECHO), BUFF);
    break;
  
  case TOK_CORCHETEIZQUIERDO:
    strncpy(tok_exp, STRINGIFY(TOK_CORCHETEIZQUIERDO), BUFF);
    break;

  case TOK_CORCHETEDERECHO:
    strncpy(tok_exp, STRINGIFY(TOK_CORCHETEDERECHO), BUFF);
    break;
  
  case TOK_LLAVEIZQUIERDA:
    strncpy(tok_exp, STRINGIFY(TOK_LLAVEIZQUIERDA), BUFF);
    break;

  case TOK_LLAVEDERECHA:
    strncpy(tok_exp, STRINGIFY(TOK_LLAVEDERECHA), BUFF);
    break;
  
  case TOK_ASIGNACION:
    strncpy(tok_exp, STRINGIFY(TOK_ASIGNACION), BUFF);
    break;
  
  case TOK_MENOS:
    strncpy(tok_exp, STRINGIFY(TOK_MENOS), BUFF);
    break;

  case TOK_DIVISION:
    strncpy(tok_exp, STRINGIFY(TOK_DIVISION), BUFF);
    break;
  
  case TOK_ASTERISCO:
    strncpy(tok_exp, STRINGIFY(TOK_ASTERISCO), BUFF);
    break;

  case TOK_AND:
    strncpy(tok_exp, STRINGIFY(TOK_AND), BUFF);
    break;
  
  case TOK_OR:
    strncpy(tok_exp, STRINGIFY(TOK_OR), BUFF);
    break;

  case TOK_NOT:
    strncpy(tok_exp, STRINGIFY(TOK_NOT), BUFF);
    break;

  case TOK_IGUAL:
    strncpy(tok_exp, STRINGIFY(TOK_IGUAL), BUFF);
    break;
  
  case TOK_DISTINTO:
    strncpy(tok_exp, STRINGIFY(TOK_DISTINTO), BUFF);
    break;

  case TOK_MENORIGUAL:
    strncpy(tok_exp, STRINGIFY(TOK_MENORIGUAL), BUFF);
    break;
  
  case TOK_MAYORIGUAL:
    strncpy(tok_exp, STRINGIFY(TOK_MAYORIGUAL), BUFF);
    break;

  case TOK_MENOR:
    strncpy(tok_exp, STRINGIFY(TOK_MENOR), BUFF);
    break;
  
  case TOK_MAYOR:
    strncpy(tok_exp, STRINGIFY(TOK_MAYOR), BUFF);
    break;

  case TOK_IDENTIFICADOR:
    strncpy(tok_exp, STRINGIFY(TOK_IDENTIFICADOR), BUFF);
    break;

  case TOK_CONSTANTE_ENTERA:
    strncpy(tok_exp, STRINGIFY(TOK_CONSTANTE_ENTERA), BUFF);
    break;
  
  case TOK_TRUE:
    strncpy(tok_exp, STRINGIFY(TOK_TRUE), BUFF);
    break;

  case TOK_FALSE:
    strncpy(tok_exp, STRINGIFY(TOK_FALSE), BUFF);
    break;
  
  default:
    break;
  }
}
