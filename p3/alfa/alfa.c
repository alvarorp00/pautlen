#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "alfa.h"

/* Externals */

extern int yyleng;
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
  
  col += yyleng;
  
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

  return 0;
}


void selectToken(int tok, char *tok_exp)
{
  switch (tok)
  {
  case TOK_MAIN:
    COPY(tok_exp, STR(TOK_MAIN));
    break;
  
  case TOK_INT:
    COPY(tok_exp, STR(TOK_INT));
    break;

  case TOK_BOOLEAN:
    COPY(tok_exp, STR(TOK_BOOLEAN));
    break;
  
  case TOK_ARRAY:
    COPY(tok_exp, STR(TOK_ARRAY));
    break;

  case TOK_FUNCTION:
    COPY(tok_exp, STR(TOK_FUNCTION));
    break;
  
  case TOK_IF:
    COPY(tok_exp, STR(TOK_IF));
    break;

  case TOK_ELSE:
    COPY(tok_exp, STR(TOK_ELSE));
    break;
  
  case TOK_WHILE:
    COPY(tok_exp, STR(TOK_WHILE));
    break;

  case TOK_SCANF:
    COPY(tok_exp, STR(TOK_SCANF));
    break;
  
  case TOK_PRINTF:
    COPY(tok_exp, STR(TOK_PRINTF));
    break;

  case TOK_PUNTOYCOMA:
    COPY(tok_exp, STR(TOK_PUNTOYCOMA));
    break;
  
  case TOK_RETURN:
    COPY(tok_exp, STR(TOK_RETURN));
    break;

  case TOK_COMA:
    COPY(tok_exp, STR(TOK_COMA));
    break;
  
  case TOK_PARENTESISIZQUIERDO:
    COPY(tok_exp, STR(TOK_PARENTESISIZQUIERDO));
    break;

  case TOK_PARENTESISDERECHO:
    COPY(tok_exp, STR(TOK_PARENTESISDERECHO));
    break;
  
  case TOK_CORCHETEIZQUIERDO:
    COPY(tok_exp, STR(TOK_CORCHETEIZQUIERDO));
    break;

  case TOK_CORCHETEDERECHO:
    COPY(tok_exp, STR(TOK_CORCHETEDERECHO));
    break;
  
  case TOK_LLAVEIZQUIERDA:
    COPY(tok_exp, STR(TOK_LLAVEIZQUIERDA));
    break;

  case TOK_LLAVEDERECHA:
    COPY(tok_exp, STR(TOK_LLAVEDERECHA));
    break;
  
  case TOK_ASIGNACION:
    COPY(tok_exp, STR(TOK_ASIGNACION));
    break;
  
  case TOK_MENOS:
    COPY(tok_exp, STR(TOK_MENOS));
    break;

  case TOK_DIVISION:
    COPY(tok_exp, STR(TOK_DIVISION));
    break;
  
  case TOK_ASTERISCO:
    COPY(tok_exp, STR(TOK_ASTERISCO));
    break;

  case TOK_AND:
    COPY(tok_exp, STR(TOK_AND));
    break;
  
  case TOK_OR:
    COPY(tok_exp, STR(TOK_OR));
    break;

  case TOK_NOT:
    COPY(tok_exp, STR(TOK_NOT));
    break;

  case TOK_IGUAL:
    COPY(tok_exp, STR(TOK_IGUAL));
    break;
  
  case TOK_DISTINTO:
    COPY(tok_exp, STR(TOK_DISTINTO));
    break;

  case TOK_MENORIGUAL:
    COPY(tok_exp, STR(TOK_MENORIGUAL));
    break;
  
  case TOK_MAYORIGUAL:
    COPY(tok_exp, STR(TOK_MAYORIGUAL));
    break;

  case TOK_MENOR:
    COPY(tok_exp, STR(TOK_MENOR));
    break;
  
  case TOK_MAYOR:
    COPY(tok_exp, STR(TOK_MAYOR));
    break;

  case TOK_IDENTIFICADOR:
    COPY(tok_exp, STR(TOK_IDENTIFICADOR));
    break;

  case TOK_CONSTANTE_ENTERA:
    COPY(tok_exp, STR(TOK_CONSTANTE_ENTERA));
    break;
  
  case TOK_TRUE:
    COPY(tok_exp, STR(TOK_TRUE));
    break;

  case TOK_FALSE:
    COPY(tok_exp, STR(TOK_FALSE));
    break;
  
  default:
    break;
  }
}
