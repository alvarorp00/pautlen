/* Seccion de definiciones */

%{

/* C delimiters */

  #include <stdio.h>
  #include <stdbool.h>
  #include "alfa.h"
  #include "symbolsTable.h"
  #include "generator.h"

  #define PRINT_RULE(str, val) fprintf(yyout, ";R%d:\t%s\n", val, str);
  #define PARSEFAIL 0

  extern char errbuff[BUFF];

  /* Function to extract tokens from morfologic */
  extern int yylex();

  /* Default input file */
  extern FILE* yyin;

  /* Default yyoutput file */
  extern FILE* yyout;

  /* Default assembly file */
  FPASM;

  /* Common morfoligic error flag defined in "alfa.h" */
  bool morfofailure;

  /* Function launched in case of failure */
  int yyerror(SymbolsTable *st, char *s);

  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
  /* - - - - - - GLOBAL VARS - - - - - - - */
  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */

  ElementCategory current_category; /* VAR, PARAM, FUNCT */
  DataType current_type; /* INT, BOOLEAN */
  IdentifierCategory current_class; /* SCALAR, VECTOR */
  Scope current_scope; /* GLOBAL, LOCAL */
  int current_pos; /* Position inside funct either params or localvars */
  int8_t current_size; /* Vector's size */
  int32_t current_params; /* Function params amount */
  int32_t current_localvars; /* Function localvars amount */

%}

%union
{
  attrs_type attrs;
}

%lex-param {SymbolsTable *st}
%parse-param {SymbolsTable *st}

%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_ASTERISCO
%token TOK_DIVISION
%token TOK_MENOR
%token TOK_MAYOR

%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL

%token TOK_CONSTANTE_ENTERA
%token TOK_TRUE
%token TOK_FALSE
%token TOK_ERROR

%token MENOSU

%token <attrs> TOK_CTE_ENTERA 
%token <attrs> TOK_IDENTIFICADOR

%type <attrs> conditional
%type <attrs> comparison
%type <attrs> vector_element
%type <attrs> exp
%type <attrs> constant
%type <attrs> constant_int
%type <attrs> constant_logic
%type <attrs> identifier

%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_ASTERISCO TOK_DIVISION TOK_AND

%right TOK_NOT MENOSU

%start program

%%

/*------------------------------------------------------*/
/*                      PROD: 1                         */
/*------------------------------------------------------*/
program: TOK_MAIN TOK_LLAVEIZQUIERDA declarations er1 functions er2 statements TOK_LLAVEDERECHA
      {
        write_end(FPASM_NAME);
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: LAMBDA1                   */
/*------------------------------------------------------*/
er1: /* empty --> write data section */
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: LAMBDA2                   */
/*------------------------------------------------------*/
er2: /* empty --> write "main:" */
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 2                         */
/*------------------------------------------------------*/
declarations: declaration
            {

            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 3                         */
/*------------------------------------------------------*/
declarations: declaration declarations
            {

            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 4                         */
/*------------------------------------------------------*/
declaration: class identifiers TOK_PUNTOYCOMA 
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 5                         */
/*------------------------------------------------------*/
class: class_scalar
      {
        current_class = SCALAR;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 7                         */
/*------------------------------------------------------*/
class: class_vector
      {
        current_class = VECTOR;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 9                         */
/*------------------------------------------------------*/
class_scalar: type
            {

            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 10                        */
/*------------------------------------------------------*/
type: TOK_INT
      {
        current_type = INT;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 10                        */
/*------------------------------------------------------*/
type: TOK_BOOLEAN
      {
        current_type = BOOLEAN;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 15                        */
/*------------------------------------------------------*/
class_vector: TOK_ARRAY type TOK_CORCHETEIZQUIERDO constant_int TOK_CORCHETEDERECHO 
            {

            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 18                        */
/*------------------------------------------------------*/
identifiers: identifier
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 19                        */
/*------------------------------------------------------*/
identifiers: identifier TOK_COMA identifiers
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 20                        */
/*------------------------------------------------------*/
functions: function functions
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 21                        */
/*------------------------------------------------------*/
functions: /* empty */
        {
          
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 22                        */
/*------------------------------------------------------*/
function: TOK_FUNCTION type identifier TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations statements TOK_LLAVEDERECHA
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 23                        */
/*------------------------------------------------------*/
function_params: function_param remaining_function_params
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 24                        */
/*------------------------------------------------------*/
function_params: /* empty */
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 25                        */
/*------------------------------------------------------*/
remaining_function_params: TOK_PUNTOYCOMA function_param remaining_function_params
                        {

                        }
                        ;

/*------------------------------------------------------*/
/*                      PROD: 26                        */
/*------------------------------------------------------*/
remaining_function_params: /* empty */
                        {

                        }
                        ;

/*------------------------------------------------------*/
/*                      PROD: 27                        */
/*------------------------------------------------------*/
function_param: type identifier
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 28                        */
/*------------------------------------------------------*/
function_declarations: declarations
                    {

                    }
                    ;

/*------------------------------------------------------*/
/*                      PROD: 29                        */
/*------------------------------------------------------*/
function_declarations: /* empty */
                    {

                    }
                    ;

/*------------------------------------------------------*/
/*                      PROD: 30                        */
/*------------------------------------------------------*/
statements: statement
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 31                        */
/*------------------------------------------------------*/
statements: statement statements
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 32                        */
/*------------------------------------------------------*/
statement: simple_statement TOK_PUNTOYCOMA
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 33                        */
/*------------------------------------------------------*/
statement: block
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 34                        */
/*------------------------------------------------------*/
simple_statement: assignment
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 35                        */
/*------------------------------------------------------*/
simple_statement: reading
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 36                        */
/*------------------------------------------------------*/
simple_statement: writing
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 38                        */
/*------------------------------------------------------*/
simple_statement: function_return
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 40                        */
/*------------------------------------------------------*/
block: conditional
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 41                        */
/*------------------------------------------------------*/
block: loop
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 43                        */
/*------------------------------------------------------*/
/* TOK_IDENTIFICADOR is identifier */
assignment: TOK_IDENTIFICADOR TOK_ASIGNACION exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 44                        */
/*------------------------------------------------------*/
assignment: vector_element TOK_ASIGNACION exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 48                        */
/*------------------------------------------------------*/
vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
              {

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 50                        */
/*------------------------------------------------------*/
conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 51                        */
/*------------------------------------------------------*/
conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 52                        */
/*------------------------------------------------------*/
loop: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 54                        */
/*------------------------------------------------------*/
reading: TOK_SCANF identifier
      {

      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 55                        */
/*------------------------------------------------------*/
writing: TOK_PRINTF exp
      {

      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 61                        */
/*------------------------------------------------------*/
function_return: TOK_RETURN exp
      {

      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 72                        */
/*------------------------------------------------------*/
exp: exp TOK_MAS exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 73                        */
/*------------------------------------------------------*/
exp: exp TOK_MENOS exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 74                        */
/*------------------------------------------------------*/
exp: exp TOK_DIVISION exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 75                        */
/*------------------------------------------------------*/
exp: exp TOK_ASTERISCO exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 76                        */
/*------------------------------------------------------*/
exp: TOK_MENOS exp %prec MENOSU
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 77                        */
/*------------------------------------------------------*/
exp: exp TOK_AND exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 78                        */
/*------------------------------------------------------*/
exp: exp TOK_OR exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 79                        */
/*------------------------------------------------------*/
exp: TOK_NOT exp
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 80                        */
/*------------------------------------------------------*/
/* TOK_IDENTIFICADOR is identifier */
exp: TOK_IDENTIFICADOR
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 81                        */
/*------------------------------------------------------*/
exp: constant
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 82                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 83                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 85                        */
/*------------------------------------------------------*/
exp: vector_element
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 88                        */
/*------------------------------------------------------*/
exp: identifier TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO
    {

    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 89                        */
/*------------------------------------------------------*/
exp_list: exp exp_remaining_list
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 90                        */
/*------------------------------------------------------*/
exp_list: /* empty */
        {

        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 91                        */
/*------------------------------------------------------*/
exp_remaining_list: TOK_COMA exp exp_remaining_list
                  {

                  }
                  ;

/*------------------------------------------------------*/
/*                      PROD: 92                        */
/*------------------------------------------------------*/
exp_remaining_list: /* empty */
                  {

                  }
                  ;

/*------------------------------------------------------*/
/*                      PROD: 93                        */
/*------------------------------------------------------*/
comparison: exp TOK_IGUAL exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 94                        */
/*------------------------------------------------------*/
comparison: exp TOK_DISTINTO exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 95                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENORIGUAL exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 96                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYORIGUAL exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 97                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENOR exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 98                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYOR exp
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 99                        */
/*------------------------------------------------------*/
constant: constant_logic
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 100                       */
/*------------------------------------------------------*/
constant: constant_int
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 102                       */
/*------------------------------------------------------*/
constant_logic: TOK_TRUE
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 103                       */
/*------------------------------------------------------*/
constant_logic: TOK_FALSE
          {

          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 104                       */
/*------------------------------------------------------*/
constant_int: TOK_CONSTANTE_ENTERA
            {

            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 108                       */
/*------------------------------------------------------*/
identifier: TOK_IDENTIFICADOR
          {
            if(st_searchCurrentScope(st, $1.lexeme) != NULL)
            {
              #line 743 "alfa.y"
              COPYERR(__FILE__, "Identifier %s already at current scope", $1.lexeme);
              return PARSEFAIL;
            }
            else
            {
              st_insertBlindCurrentScope(
                st,
                $1.lexeme,
                current_category,
                current_type,
                current_class,
                current_scope,
                current_pos,
                current_size,
                current_params,
                current_localvars
              );
            }
          }
          ;

%%

/* User functions definitions */

int yyerror(SymbolsTable *st, char *s)
{
  if(morfofailure)
  {
    return -1;
  }
  
  COPYERR("alfa.y", "Syntactic error: %s", s);
  
  return -1;
}