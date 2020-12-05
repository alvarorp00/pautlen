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

program: TOK_MAIN TOK_LLAVEIZQUIERDA declarations functions statements TOK_LLAVEDERECHA {  };

declarations: declaration {  }
            | declaration declarations {  }
            ;

declaration: class identifiers TOK_PUNTOYCOMA {  };

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

class_vector: TOK_ARRAY type TOK_CORCHETEIZQUIERDO constant_int TOK_CORCHETEDERECHO {  };

identifiers: identifier {  }
          | identifier TOK_COMA identifiers {  }
          ;

functions: function functions {  }
        | /* empty */ {  }
        ;

function: TOK_FUNCTION type identifier TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations statements TOK_LLAVEDERECHA {  };

function_params: function_param remaining_function_params {  }
              | /* empty */ {  }
              ;

remaining_function_params: TOK_PUNTOYCOMA function_param remaining_function_params {  }
                        | /* empty */ {  }
                        ;

function_param: type identifier {  };

function_declarations: declarations {  }
                    | /* empty */ {  }
                    ;

statements: statement {  }
          | statement statements {  }
          ;

statement: simple_statement TOK_PUNTOYCOMA {  }
        | block {  }
        ;

simple_statement: assignment {  }
              | reading {  }
              | writing {  }
              | function_return {  }
              ;

block: conditional {  }
    | loop {  }
    ;

assignment: identifier TOK_ASIGNACION exp  {  }
          | vector_element TOK_ASIGNACION exp {  }
          ;

vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {  };

conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", RULE_CONDITIONAL); }
          | TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", RULE_CONDITIONAL + 1); }
          ;

loop: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", RULE_LOOP); };

reading: TOK_SCANF identifier { PRINT_RULE("<lectura> ::= scanf <identificador>", RULE_READING); };

writing: TOK_PRINTF exp { PRINT_RULE("<escritura> ::= printf <exp>", RULE_WRITING); };

function_return: TOK_RETURN exp { PRINT_RULE("<retorno_funcion> ::= return <exp>", RULE_FUNCTION_RETURN); };

exp: exp TOK_MAS exp {  }
    | exp TOK_MENOS exp {  }
    | exp TOK_DIVISION exp {  }
    | exp TOK_ASTERISCO exp {  }
    | TOK_MENOS exp %prec MENOSU {  }
    | exp TOK_AND exp {  }
    | exp TOK_OR exp {  }
    | TOK_NOT exp {  }
    | identifier {  }
    | constant {  }
    | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {  } 
    | TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO {  }
    | vector_element {  }
    | identifier TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO {  }
    ;

exp_list: exp exp_remaining_list {  }
        | /* empty */ {  }
        ;

exp_remaining_list: TOK_COMA exp exp_remaining_list {  }
                  | /* empty */ {  }
                  ;

comparison: exp TOK_IGUAL exp {  }
          | exp TOK_DISTINTO exp {  }
          | exp TOK_MENORIGUAL exp {  }
          | exp TOK_MAYORIGUAL exp {  }
          | exp TOK_MENOR exp {  }
          | exp TOK_MAYOR exp {  }
          ;
          

constant: constant_logic {  }
        | constant_int {  }
        ;

constant_logic: TOK_TRUE {  }
              | TOK_FALSE {  }
              ;

constant_int: TOK_CONSTANTE_ENTERA {  };

identifier: TOK_IDENTIFICADOR {  }

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