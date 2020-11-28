/* Seccion de definiciones */

%{

/* C delimiters */

  #include <stdio.h>
  #include <stdbool.h>
  #include "alfa.h"
  #include "rules.h"

  #define PRINT_RULE(str, val) fprintf(yyout, ";R%d:\t%s\n", val, str);

  extern char errbuff[BUFF];

  extern int yylex();
  extern FILE* yyin;
  extern FILE* yyout;

  bool morfofailure;

  int yyerror(char *s);

  int yylex();

%}

%union
    {
      char* str;
      int num;
    }

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

%token <num> TOK_CTE_ENTERA 
%token <str> TOK_IDENTIFICADOR

%token TOK_CONSTANTE_ENTERA
%token TOK_TRUE
%token TOK_FALSE
%token TOK_ERROR

%left TOK_MAS TOK_MENOS
%left TOK_ASTERISCO TOK_DIVISION

%right TOK_NOT

%start program

%%

program: TOK_MAIN TOK_LLAVEIZQUIERDA declarations functions statements TOK_LLAVEDERECHA { PRINT_RULE("<programa> ::= main { <declaraciones> <funciones> <sentencias> }", RULE_PROGRAM); };

declarations: declaration { PRINT_RULE("<declaraciones> ::= <declaracion>", RULE_DECLARATIONS); }
            | declaration declarations { PRINT_RULE("<declaraciones> ::= <declaracion> <declaraciones>", RULE_DECLARATIONS + 1); }
            ;

declaration: class identifiers TOK_PUNTOYCOMA { PRINT_RULE("<declaracion> ::= <clase> <identificadores> ;", RULE_DECLARATION); };

class: class_scalar { PRINT_RULE("<clase> ::= <clase_escalar>", RULE_CLASS); }
      | class_vector { PRINT_RULE("<clase> ::= <clase_vector>", RULE_CLASS + 2); }
      ;

class_scalar: type { PRINT_RULE("<clase_escalar> ::= <tipo> ", RULE_CLASS_SCALAR); };

type: TOK_INT { PRINT_RULE("<tipo> ::= int", RULE_TYPE); }
    | TOK_BOOLEAN { PRINT_RULE("<tipo> ::= boolean", RULE_TYPE + 1); }
    ;

class_vector: TOK_ARRAY type TOK_CORCHETEIZQUIERDO constant_int TOK_CORCHETEDERECHO { PRINT_RULE("<clase_vector> ::= array <tipo> [ <constante_entera> ]", RULE_CLASS_VECTOR); };

identifiers: identifier { PRINT_RULE("<identificadores> ::= <identificador>", RULE_IDENTIFIERS); }
          | identifier TOK_COMA identifiers { PRINT_RULE("<identificadores> ::= <identificador> , <identificadores>", RULE_IDENTIFIERS + 1); }
          ;

functions: function functions { PRINT_RULE("<funciones> :: <funcion> <funciones>", RULE_FUNCTIONS); }
        | { PRINT_RULE("<funciones> ::= ", RULE_FUNCTIONS + 1); }
        ;

function: TOK_FUNCTION type identifier TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations statements TOK_LLAVEDERECHA { PRINT_RULE("<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }", RULE_FUNCTION); };

function_params: function_params remaining_function_params { PRINT_RULE("<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>", RULE_FUNCTION_PARAMS); }
              | { PRINT_RULE("<parametros_funcion> ::= ", RULE_FUNCTION_PARAMS + 1); }
              ;

remaining_function_params: TOK_PUNTOYCOMA function_param remaining_function_params { PRINT_RULE("<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>", RULE_FUNCTION_REMAINING_PARAMS); }
                        | { PRINT_RULE("<resto_parametros_funcion> ::= ", RULE_FUNCTION_REMAINING_PARAMS + 1); }
                        ;

function_param: type identifier { PRINT_RULE("<parametro_funcion> ::= <tipo> <identificador>", RULE_FUNCTION_PARAM); };

function_declarations: declarations { PRINT_RULE("<declaraciones_funcion> ::= <declaraciones>", RULE_FUNCTION_DECLARE) }
                    | { PRINT_RULE("<declaraciones_funcion> ::= ", RULE_FUNCTION_DECLARE + 1); }
                    ;

statements: statement { PRINT_RULE("<sentencias> ::= <sentencia>", RULE_STATEMENTS); }
          | statement statements { PRINT_RULE("<sentencias> ::= <sentencia> <sentencias>", RULE_STATEMENTS + 1); }
          ;

statement: simple_statement TOK_PUNTOYCOMA { PRINT_RULE("<sentencia> ::= <sentecia_simple> ;", RULE_STATEMENT); }
        | block { PRINT_RULE("<sentencia> ::= <bloque>", RULE_STATEMENT + 1); }
        ;

simple_statement: assignment { PRINT_RULE("<sentecia_simple> ::= <asignacion>", RULE_STATEMENT_SIMPLE); }
              | reading { PRINT_RULE("<sentecia_simple> ::= <lectura>", RULE_STATEMENT_SIMPLE + 1); }
              | writing { PRINT_RULE("<sentecia_simple> ::= <escritura>", RULE_STATEMENT_SIMPLE + 2); }
              | function_return { PRINT_RULE("<sentecia_simple> ::= <retorno_funcion>", RULE_STATEMENT_SIMPLE + 4); }
              ;

block: conditional { PRINT_RULE("<bloque> ::= <condicional>", RULE_BLOCK); }
    | loop { PRINT_RULE("<bloque> ::= <bubcle>", RULE_BLOCK + 1); }
    ;

assignment: identifier TOK_ASIGNACION exp  { PRINT_RULE("<asignacion> ::= <identificador> = <exp>", RULE_ASSIGNMENT); }
          | vector_element TOK_ASIGNACION exp { PRINT_RULE("<asignacion> ::= <elemento_vector> = <exp>", RULE_ASSIGNMENT + 1); }
          ;

vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO { PRINT_RULE("<elemento_vector> ::= <identificador> [ <exp> ]", RULE_ARRAY_ELEM); };

conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", RULE_CONDITIONAL); }
          | TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", RULE_CONDITIONAL + 1); }
          ;

loop: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA { PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", RULE_LOOP); };

reading: TOK_SCANF identifier { PRINT_RULE("<lectura> ::= scanf <identificador>", RULE_READING); };

writing: TOK_PRINTF exp { PRINT_RULE("<escritura> ::= printf <exp>", RULE_WRITING); };

function_return: TOK_RETURN exp { PRINT_RULE("<retorno_funcion> ::= return <exp>", RULE_FUNCTION_RETURN); };

exp: exp TOK_MAS exp { PRINT_RULE("<exp> ::= <exp> + <exp>", RULE_EXP); }
    | exp TOK_MENOS exp { PRINT_RULE("<exp> ::= <exp> - <exp>", RULE_EXP + 1); }
    | exp TOK_DIVISION exp { PRINT_RULE("<exp> ::= <exp> / <exp>", RULE_EXP + 3); }
    | exp TOK_ASTERISCO exp { PRINT_RULE("<exp> ::= <exp> * <exp>", RULE_EXP + 2); }
    | TOK_MENOS exp { PRINT_RULE("<exp> ::= - <exp>", RULE_EXP + 4); }
    | exp TOK_AND exp { PRINT_RULE("<exp> ::= <exp> && <exp>", RULE_EXP + 5); }
    | exp TOK_OR exp { PRINT_RULE("<exp> ::= <exp> || <exp>", RULE_EXP + 6); }
    | TOK_NOT exp { PRINT_RULE("<exp> ::= ! <exp>", RULE_EXP + 7); }
    | identifier { PRINT_RULE("<exp> ::= <identificador>", RULE_EXP + 8); }
    | constant { PRINT_RULE("<exp> ::= <constante>", RULE_EXP + 9); }
    | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO { PRINT_RULE("<exp> ::= ( <exp> )", RULE_EXP + 10); } 
    | TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO { PRINT_RULE("<exp> ::= ( <comparacion> )", RULE_EXP + 11); }
    | vector_element { PRINT_RULE("<exp> ::= <exp> + <exp>", RULE_EXP + 13); }
    | identifier TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO { PRINT_RULE("<exp> ::= <identificador> ( <lista_expresiones> )", RULE_EXP + 16); }
    ;

exp_list: exp exp_remaining_list { PRINT_RULE("<lista_expresiones> ::= <exp> <resto_lista_expresiones>", RULE_EXP_LIST); }
        | { PRINT_RULE("<lista_expresiones> ::= ", RULE_EXP_LIST + 1); }
        ;

exp_remaining_list: TOK_COMA exp exp_remaining_list { PRINT_RULE("<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>", RULE_EXP_REM_LIST); }
                  | { PRINT_RULE("<resto_lista_expresiones> ::= ", RULE_EXP_REM_LIST + 1); }
                  ;

comparison: exp TOK_IGUAL exp { PRINT_RULE("<comparacion> ::= <exp> == <exp>", RULE_COMP); }
          | exp TOK_DISTINTO exp { PRINT_RULE("<comparacion> ::= <exp> != <exp>", RULE_COMP + 1); }
          | exp TOK_MENORIGUAL exp { PRINT_RULE("<comparacion> ::= <exp> <= <exp>", RULE_COMP + 2); }
          | exp TOK_MAYORIGUAL exp { PRINT_RULE("<comparacion> ::= <exp> >= <exp>", RULE_COMP + 3); }
          | exp TOK_MENOR exp { PRINT_RULE("<comparacion> ::= <exp> < <exp>", RULE_COMP + 4); }
          | exp TOK_MAYOR exp { PRINT_RULE("<comparacion> ::= <exp> > <exp>", RULE_COMP + 5); }
          ;
          

constant: constant_logic { PRINT_RULE("<constante> ::= <constante_logica>", RULE_CONST); }
        | constant_int { PRINT_RULE("<constante> ::= <constante_entera>", RULE_CONST + 1); }
        ;

constant_logic: TOK_TRUE { PRINT_RULE("<constante_logica> ::= true", RULE_CONST_LOGIC); }
              | TOK_FALSE { PRINT_RULE("<constante_logica> ::= false", RULE_CONST_LOGIC + 1); }
              ;

constant_int: TOK_CONSTANTE_ENTERA { PRINT_RULE("<constante_entera> ::= TOK_CONSTANTE_ENTERA", RULE_CONST_INT); };

identifier: TOK_IDENTIFICADOR { PRINT_RULE("<identificador> ::= TOK_IDENTIFICADOR", RULE_IDENTIFIER); }

%%

/* User functions definitions */

int yyerror(char *s)
{
  if(morfofailure)
  {
    fprintf(yyout, "ERROR MORFOLOGICO: %s.\n", errbuff);
    return -1;
  }
  
  fprintf(yyout, "ERROR SINTACTICO: %s.\n", s);
  return -1;
}