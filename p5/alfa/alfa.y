/* Seccion de definiciones */

%{

/* C delimiters */

  #include <stdio.h>
  #include <stdbool.h>
  #include "alfa.h"
  #include "symbolsTable.h"
  #include "rules.h"

  #define PRINT_RULE(str, val) fprintf(yyout, ";R%d:\t%s\n", val, str);

  extern char errbuff[BUFF];

  /* Function to extract tokens from morfologic */
  extern int yylex();

  /* Default input file */
  extern FILE* yyin;

  /* Default output file */
  extern FILE* yyout;

  /* Common morfoligic error flag defined in "alfa.h" */
  bool morfofailure;

  /* Function launched in case of failure */
  int yyerror(SymbolsTable *st, char *s);

  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
  /* - - - - - - GLOBAL VARS - - - - - - - */
  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */

  DataType current_type;
  IdentifierCategory current_class;

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
program: TOK_MAIN TOK_LLAVEIZQUIERDA declarations functions statements TOK_LLAVEDERECHA
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

class_scalar: type {  };

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

statements: statement
          {

          }
          ;

statements: statement statements
          {

          }
          ;

statement: simple_statement TOK_PUNTOYCOMA
        {

        }
        ;

statement: block
        {

        }
        ;

simple_statement: assignment
              {

              }
              ;

simple_statement: reading
              {

              }
              ;

simple_statement: writing
              {

              }
              ;

simple_statement: function_return
              {

              }
              ;

block: conditional
    {

    }
    ;

block: loop
    {

    }
    ;

assignment: identifier TOK_ASIGNACION exp
    {

    }
    ;

assignment: vector_element TOK_ASIGNACION exp
    {

    }
    ;

vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
              {

              }
              ;

conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {

          }
          ;

conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {

          }
          ;

loop: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
    {

    }
    ;

reading: TOK_SCANF identifier
      {

      }
      ;

writing: TOK_PRINTF exp
      {

      }
      ;

function_return: TOK_RETURN exp
      {

      }
      ;

exp: exp TOK_MAS exp
    {

    }
    ;

exp: exp TOK_MENOS exp
    {

    }
    ;

exp: exp TOK_DIVISION exp
    {

    }
    ;

exp: exp TOK_ASTERISCO exp
    {

    }
    ;

exp: TOK_MENOS exp %prec MENOSU
    {

    }
    ;

exp: exp TOK_AND exp
    {

    }
    ;

exp: exp TOK_OR exp
    {

    }
    ;

exp: TOK_NOT exp
    {

    }
    ;

exp: identifier
    {

    }
    ;

exp: constant
    {

    }
    ;

exp: TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
    {

    }
    ;

exp: TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO
    {

    }
    ;

exp: vector_element
    {

    }
    ;

exp: identifier TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO
    {

    }
    ;

exp_list: exp exp_remaining_list
        {

        }
        ;

exp_list: /* empty */
        {

        }
        ;

exp_remaining_list: TOK_COMA exp exp_remaining_list
                  {

                  }
                  ;

exp_remaining_list: /* empty */
                  {

                  }
                  ;

comparison: exp TOK_IGUAL exp
          {

          }
          ;

comparison: exp TOK_DISTINTO exp
          {

          }
          ;

comparison: exp TOK_MENORIGUAL exp
          {

          }
          ;

comparison: exp TOK_MAYORIGUAL exp
          {

          }
          ;

comparison: exp TOK_MENOR exp
          {

          }
          ;

comparison: exp TOK_MAYOR exp
          {

          }
          ;

constant: constant_logic
          {

          }
          ;

constant: constant_int
          {

          }
          ;

constant: TOK_TRUE
          {

          }
          ;

constant: TOK_FALSE
          {

          }
          ;

constant_int: TOK_CONSTANTE_ENTERA
            {

            }
            ;

identifier: TOK_IDENTIFICADOR
          {

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