/* Seccion de definiciones */

%{

/* C delimiters */

  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include "alfa.h"
  #include "symbolsTable.h"
  #include "generator.h"

  #ifdef _DEBUG_
  #define PRINT_RULE(str, val) \
              fprintf(stdout, ";R%d:\t%s\n", val, str);
  #else
  #define PRINT_RULE(str, val)
  #endif
  
  #define PARSEFAIL INT_MAX

  extern char errbuff[BUFF];

  /* Function to extract tokens from morfologic */
  extern int yylex(SymbolsTable *st);

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

  void write_symbols_table(FPASM, SymbolsTable *st);

  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
  /* - - - - - - GLOBAL VARS - - - - - - - */
  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */

  Symbol *_sgeneric;
  Symbol *_sleft;
  Symbol *_sright;
  Symbol *_smid;

  char __buff[MAX_LEN + 1];

  ElementCategory current_category; /* VAR, PARAM, FUNCT */
  DataType current_type; /* INT, BOOLEAN */
  IdentifierCategory current_class; /* SCALAR, VECTOR */
  Scope current_scope; /* GLOBAL, LOCAL */
  int current_pos; /* Position inside funct either params or localvars */
  int8_t current_size; /* Vector's size */
  int32_t current_params; /* Function params amount */
  int32_t current_localvars; /* Function localvars amount */

  bool in_declare; /* true if we're in declarations part, false if not */
  bool in_main; /* true if we're in main part, else false */
  
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

%token TOK_TRUE
%token TOK_FALSE
%token TOK_ERROR

%token MENOSU

%token <attrs> TOK_CONSTANTE_ENTERA 
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
        PRINT_RULE("<programa> ::= main { <declaraciones> <funciones> <sentencias> }", 1);
        write_end(FPASM_NAME);
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: LAMBDA1                   */
/*------------------------------------------------------*/
er1: /* empty --> write data section */
    {
      write_data_header(FPASM_NAME);
      write_bss_header(FPASM_NAME);
      write_symbols_table(FPASM_NAME, st);
      write_code_segment(FPASM_NAME);
      in_declare = false;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: LAMBDA2                   */
/*------------------------------------------------------*/
er2: /* empty --> write "main:" */
    {
      write_main_begin(FPASM_NAME);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 2                         */
/*------------------------------------------------------*/
declarations: declaration
            {
              PRINT_RULE("<declaraciones> ::= <declaracion>", 2);
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 3                         */
/*------------------------------------------------------*/
declarations: declaration declarations
            {
              PRINT_RULE("<declaraciones> ::= <declaracion> <declaraciones>", 3);
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 4                         */
/*------------------------------------------------------*/
declaration: class identifiers TOK_PUNTOYCOMA 
          {
            PRINT_RULE("<declaracion> ::= <clase> <identificadores> ;", 4);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 5                         */
/*------------------------------------------------------*/
class: class_scalar
      {
        PRINT_RULE("<clase> ::= <clase_escalar>", 5);
        current_class = SCALAR;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 7                         */
/*------------------------------------------------------*/
class: class_vector
      {
        PRINT_RULE("<clase> ::= <clase_vector>", 7);
        current_class = VECTOR;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 9                         */
/*------------------------------------------------------*/
class_scalar: type
            {
              PRINT_RULE("<clase_escalar> ::= <tipo> ", 9);
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 10                        */
/*------------------------------------------------------*/
type: TOK_INT
      {
        PRINT_RULE("<tipo> ::= int", 10);
        current_type = INT;
      }
      ;

/*------------------------------------------------------*/
/*------------------------------------------------------*/
type: TOK_BOOLEAN
      {
        PRINT_RULE("<tipo> ::= boolean", 11);
        current_type = BOOLEAN;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 15                        */
/*------------------------------------------------------*/
class_vector: TOK_ARRAY type TOK_CORCHETEIZQUIERDO constant_int TOK_CORCHETEDERECHO 
            {
              PRINT_RULE("<clase_vector> ::= array <tipo> [ <constante_entera> ]", 15);
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 18                        */
/*------------------------------------------------------*/
identifiers: identifier
          {
            PRINT_RULE("<identificadores> ::= <identificador>", 18);
          }
          ;
 
/*------------------------------------------------------*/
/*                      PROD: 19                        */
/*                      PROD: 11                        */
/*------------------------------------------------------*/
identifiers: identifier TOK_COMA identifiers
          {
            PRINT_RULE("<identificadores> ::= <identificador> , <identificadores>", 19);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 20                        */
/*------------------------------------------------------*/
functions: function functions
        {
          PRINT_RULE("<funciones> :: <funcion> <funciones>", 20);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 21                        */
/*------------------------------------------------------*/
functions: /* empty */
        {
          PRINT_RULE("<funciones> ::= ", 21);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 22                        */
/*------------------------------------------------------*/
function: TOK_FUNCTION type identifier TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA function_declarations statements TOK_LLAVEDERECHA
        {
          PRINT_RULE("<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }", 22);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 23                        */
/*------------------------------------------------------*/
function_params: function_param remaining_function_params
              {
                PRINT_RULE("<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>", 23);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 24                        */
/*------------------------------------------------------*/
function_params: /* empty */
              {
                PRINT_RULE("<parametros_funcion> ::= ", 24);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 25                        */
/*------------------------------------------------------*/
remaining_function_params: TOK_PUNTOYCOMA function_param remaining_function_params
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>", 25);
                        }
                        ;

/*------------------------------------------------------*/
/*                      PROD: 26                        */
/*------------------------------------------------------*/
remaining_function_params: /* empty */
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ", 26);
                        }
                        ;

/*------------------------------------------------------*/
/*                      PROD: 27                        */
/*------------------------------------------------------*/
function_param: type identifier
              {
                PRINT_RULE("<parametro_funcion> ::= <tipo> <identificador>", 27);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 28                        */
/*------------------------------------------------------*/
function_declarations: declarations
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= <declaraciones>", 28);
                    }
                    ;

/*------------------------------------------------------*/
/*                      PROD: 29                        */
/*------------------------------------------------------*/
function_declarations: /* empty */
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= ", 29);
                    }
                    ;

/*------------------------------------------------------*/
/*                      PROD: 30                        */
/*------------------------------------------------------*/
statements: statement
          {
            PRINT_RULE("<sentencias> ::= <sentencia>", 30);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 31                        */
/*------------------------------------------------------*/
statements: statement statements
          {
            PRINT_RULE("<sentencias> ::= <sentencia> <sentencias>", 31);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 32                        */
/*------------------------------------------------------*/
statement: simple_statement TOK_PUNTOYCOMA
        {
          PRINT_RULE("<sentencia> ::= <sentencia_simple> ;", 32);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 33                        */
/*------------------------------------------------------*/
statement: block
        {
          PRINT_RULE("<sentencia> ::= <bloque>", 33);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 34                        */
/*------------------------------------------------------*/
simple_statement: assignment
              {
                PRINT_RULE("<sentencia_simple> ::= <asignacion>", 34);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 35                        */
/*------------------------------------------------------*/
simple_statement: reading
              {
                PRINT_RULE("<sentencia_simple> ::= <lectura>", 35);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 36                        */
/*------------------------------------------------------*/
simple_statement: writing
              {
                PRINT_RULE("<sentencia_simple> ::= <escritura>", 36);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 38                        */
/*------------------------------------------------------*/
simple_statement: function_return
              {
                PRINT_RULE("<sentencia_simple> ::= <retorno_funcion>", 38);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 40                        */
/*------------------------------------------------------*/
block: conditional
    {
      PRINT_RULE("<bloque> ::= <condicional>", 40);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 41                        */
/*------------------------------------------------------*/
block: loop
    {
      PRINT_RULE("<bloque> ::= <bubcle>", 41);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 43                        */
/*------------------------------------------------------*/
/* should be "assignment: identifier TOK_ASIGNACION etc.." */
assignment: TOK_IDENTIFICADOR TOK_ASIGNACION exp
    {
      PRINT_RULE("<asignacion> ::= <identificador> = <exp>", 43);
      if((_sleft = st_searchCurrentScope(st, $1.lexeme)) == NULL)
      {
        /* Symbol is not declared */
        COPYERR("Identifier %s not declared.", $1.lexeme); 
        return PARSEFAIL;
      }
      if(symbol_get_category(_sleft) == FUNCT)
      {
        COPYERR("Identifier %s is a function.", $1.lexeme); 
        return PARSEFAIL;
      }
      else if(symbol_blind_identifierCategory(_sleft) == VECTOR)
      {
        COPYERR("Identifier %s is a vector.", $1.lexeme); 
        return PARSEFAIL;
      }
      else if(symbol_blind_dataType(_sleft) != $3.type)
      {
        COPYERR("Identifiers type missmatch");
        return PARSEFAIL;
      }
      write_assignment(FPASM_NAME, $1.lexeme, $3.is_var);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 44                        */
/*------------------------------------------------------*/
assignment: vector_element TOK_ASIGNACION exp
    {
      PRINT_RULE("<asignacion> ::= <elemento_vector> = <exp>", 44);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 48                        */
/*------------------------------------------------------*/
vector_element: identifier TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
              {
                PRINT_RULE("<elemento_vector> ::= <identificador> [ <exp> ]", 48);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 50                        */
/*------------------------------------------------------*/
conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", 50);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 51                        */
/*------------------------------------------------------*/
conditional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", 51);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 52                        */
/*------------------------------------------------------*/
loop: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
    {
      PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", 52);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 54                        */
/*------------------------------------------------------*/
reading: TOK_SCANF TOK_IDENTIFICADOR
      {
        PRINT_RULE("<lectura> ::= scanf <identificador>", 54);

        if((_sgeneric = st_searchCurrentScope(st, $2.lexeme)) == NULL)
        {
          COPYERR("Identifier not found");
          return PARSEFAIL;
        }
        if(symbol_get_category(_sgeneric) == FUNCT)
        {
          COPYERR("Trying to print a function");
          return PARSEFAIL;
        }
        else if(symbol_blind_identifierCategory(_sgeneric) == VECTOR)
        {
          COPYERR("Trying to print a vector");
          return PARSEFAIL;
        }
        write_reading(FPASM_NAME, $2.lexeme, $2.type);
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 56                        */
/*------------------------------------------------------*/
writing: TOK_PRINTF exp
      {
        PRINT_RULE("<escritura> ::= printf <exp>", 56);

        write_writing(FPASM_NAME, $2.is_var, $2.type);

      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 61                        */
/*------------------------------------------------------*/
function_return: TOK_RETURN exp
      {
        PRINT_RULE("<retorno_funcion> ::= return <exp>", 61);
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 72                        */
/*------------------------------------------------------*/
exp: exp TOK_MAS exp
    {
      PRINT_RULE("<exp> ::= <exp> + <exp>", 72);
      if($1.type != $3.type || ($1.type != INT && $1.type != BOOLEAN))
      {
        COPYERR("Types missmatch");
        return PARSEFAIL;
      }
      write_sum(FPASM_NAME, $1.is_var, $3.is_var);
      $$.type = $1.type; // also $$.type = $3.type
      $$.is_dir = false;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 73                        */
/*------------------------------------------------------*/
exp: exp TOK_MENOS exp
    {
      PRINT_RULE("<exp> ::= <exp> - <exp>", 73);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 74                        */
/*------------------------------------------------------*/
exp: exp TOK_DIVISION exp
    {
      PRINT_RULE("<exp> ::= <exp> / <exp>", 74);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 75                        */
/*------------------------------------------------------*/
exp: exp TOK_ASTERISCO exp
    {
      PRINT_RULE("<exp> ::= <exp> * <exp>", 75);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 76                        */
/*------------------------------------------------------*/
exp: TOK_MENOS exp %prec MENOSU
    {
      PRINT_RULE("<exp> ::= - <exp>", 76);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 77                        */
/*------------------------------------------------------*/
exp: exp TOK_AND exp
    {
      PRINT_RULE("<exp> ::= <exp> && <exp>", 77);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 78                        */
/*------------------------------------------------------*/
exp: exp TOK_OR exp
    {
      PRINT_RULE("<exp> ::= <exp> || <exp>", 78);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 79                        */
/*------------------------------------------------------*/
exp: TOK_NOT exp
    {
      PRINT_RULE("<exp> ::= ! <exp>", 79);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 80                        */
/*------------------------------------------------------*/
/* should be "exp: identifier" */
exp: TOK_IDENTIFICADOR
    {
      PRINT_RULE("<exp> ::= <identificador>", 80);
      if((_sleft = st_searchCurrentScope(st, $1.lexeme)) == NULL)
      {
        COPYERR("Identifier %s doesn't exists", $1.lexeme);
        return PARSEFAIL;
      }
      if(symbol_get_category(_sleft) == FUNCT)
      {
        COPYERR("Identifier %s is a function", $1.lexeme);
        return PARSEFAIL;
      }
      else if(symbol_blind_identifierCategory(_sleft) == VECTOR)
      {
        COPYERR("Identifier %s is a vector", $1.lexeme);
        return PARSEFAIL;
      }
      $$.type = symbol_blind_dataType(_sleft);
      $$.is_var = true;

      write_operand(FPASM_NAME, $1.lexeme, $$.is_var);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 81                        */
/*------------------------------------------------------*/
exp: constant
    {
      PRINT_RULE("<exp> ::= <constante>", 81);
      $$.type = $1.type;
      $$.is_var = $1.is_var;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 82                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= ( <exp> )", 82);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 83                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= ( <comparacion> )", 83);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 85                        */
/*------------------------------------------------------*/
exp: vector_element
    {
      PRINT_RULE("<exp> ::= <elemento_vector>", 85);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 88                        */
/*------------------------------------------------------*/
exp: identifier TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= <identificador> ( <lista_expresiones> )", 88);
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 89                        */
/*------------------------------------------------------*/
exp_list: exp exp_remaining_list
        {
          PRINT_RULE("<lista_expresiones> ::= <exp> <resto_lista_expresiones>", 89);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 90                        */
/*------------------------------------------------------*/
exp_list: /* empty */
        {
          PRINT_RULE("<lista_expresiones> ::= ", 90);
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 91                        */
/*------------------------------------------------------*/
exp_remaining_list: TOK_COMA exp exp_remaining_list
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>", 91);
                  }
                  ;

/*------------------------------------------------------*/
/*                      PROD: 92                        */
/*------------------------------------------------------*/
exp_remaining_list: /* empty */
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= ", 92);
                  }
                  ;

/*------------------------------------------------------*/
/*                      PROD: 93                        */
/*------------------------------------------------------*/
comparison: exp TOK_IGUAL exp
          {
            PRINT_RULE("<comparacion> ::= <exp> == <exp>", 93);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 94                        */
/*------------------------------------------------------*/
comparison: exp TOK_DISTINTO exp
          {
            PRINT_RULE("<comparacion> ::= <exp> != <exp>", 94);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 95                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENORIGUAL exp
          {
            PRINT_RULE("<comparacion> ::= <exp> <= <exp>", 95);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 96                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYORIGUAL exp
          {
            PRINT_RULE("<comparacion> ::= <exp> >= <exp>", 96);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 97                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENOR exp
          {
            PRINT_RULE("<comparacion> ::= <exp> < <exp>", 97);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 98                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYOR exp
          {
            PRINT_RULE("<comparacion> ::= <exp> > <exp>", 98);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 99                        */
/*------------------------------------------------------*/
constant: constant_logic
          {
            PRINT_RULE("<constante> ::= <constante_logica>", 99);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 100                       */
/*------------------------------------------------------*/
constant: constant_int
          {
            PRINT_RULE("<constante> ::= <constante_entera>", 100);
            $$.type = $1.type;
            $$.is_var = $1.is_var;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 102                       */
/*------------------------------------------------------*/
constant_logic: TOK_TRUE
          {
            PRINT_RULE("<constante_logica> ::= true", 102);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 103                       */
/*------------------------------------------------------*/
constant_logic: TOK_FALSE
          {
            PRINT_RULE("<constante_logica> ::= false", 103);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 104                       */
/*------------------------------------------------------*/
constant_int: TOK_CONSTANTE_ENTERA
            {
              PRINT_RULE("<constante_entera> ::= TOK_CONSTANTE_ENTERA", 104);
              $$.type = INT;
              $$.is_var = false;
              $$.int_value = $1.int_value;
              /* push */
              snprintf(__buff, MAX_LEN, "%d", $1.int_value);
              write_operand(FPASM_NAME, __buff, false);
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 108                       */
/*------------------------------------------------------*/
identifier: TOK_IDENTIFICADOR
          {
            PRINT_RULE("<identificador> ::= TOK_IDENTIFICADOR", 108);
            if(st_searchCurrentScope(st, $1.lexeme) != NULL)
            {
              COPYERR("Identifier %s already at current scope", $1.lexeme);
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
  
  COPYERR("Syntactic error: %s", s);
  
  return -1;
}

void write_symbols_table(FPASM, SymbolsTable *st)
{
  hash_iterator *iterator;
  iterator_node *__inode;
  Symbol *__s;
  int32_t size;
  
  if(!FPASM_NAME || !st)
    return;

  iterator = hash_iterate(st_getScopeHash(st));
  if(!iterator)
    return;
  
  if(!first(iterator))
    return;

  for(__inode = first(iterator); __inode != NULL; __inode = next(__inode))
  {
    __s = (Symbol*)iter_nodeInfo(__inode);

    if(symbol_get_category(__s) != VAR)
      continue;
    if(symbol_get_var_identifierCategory(__s) == SCALAR)
    {
      write_var_declaration(FPASM_NAME, symbol_get_key(__s), SCALAR, 1);
    }
    else
    {
      size = symbol_get_var_size(__s);
      write_var_declaration(FPASM_NAME, symbol_get_key(__s), VECTOR, size);
    }
  }
  
  hash_iterate_clean(iterator);
}