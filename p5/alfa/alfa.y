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

  #define EXITFAIL(str, ...) \
              COPYERR(" "str " ", ##__VA_ARGS__); \
              return PARSEFAIL;
  
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

  Symbol *_funct;

  char __buff[MAX_LEN + 1];
  int32_t i;
  
  ElementCategory current_category; /* VAR, PARAM, FUNCT */
  DataType current_type; /* INT, BOOLEAN */
  IdentifierCategory current_class; /* SCALAR, VECTOR */
  Scope current_scope; /* GLOBAL, LOCAL */
  int32_t current_var_pos; /* Position inside funct localvars */
  int32_t current_param_pos; /* Position inside funct params */
  int8_t current_vector_size; /* Vector's size */
  int32_t current_params; /* Function params amount */
  int32_t current_localvars; /* Function localvars amount */
  uint32_t tags = 0; /* Current tags amount */

  int32_t current_call_param_count; /* Params in actual call */
  bool in_declare; /* true if we're in declarations part, false if not */
  bool in_expList; /* true if we're in exp list part, else false */
  bool in_main; /* true if we're in main part, else false */
  bool in_fn_call; /* true if we're in function call, else false */
  bool has_return; /* to control if function has return or not */
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
%type <attrs> if_exp
%type <attrs> if_exp_stm
%type <attrs> loop
%type <attrs> while_exp
%type <attrs> while

%type <attrs> type

%type <attrs> function
%type <attrs> fn_name
%type <attrs> fn_declarations
%type <attrs> function_param_identifier
%type <attrs> fidf_funct_call
%type <attrs> fer1
%type <attrs> fer2

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
            in_declare = true;
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
              
              current_vector_size = $4.int_value;
              if( current_vector_size < _VECTOR_MIN_LEN_ ||
                    current_vector_size > _VECTOR_MAX_LEN_ )
              {
                EXITFAIL("Vector's size out of allowed bounds");
              }
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
function: fer2 /* fn_declarations */  fer1 statements TOK_LLAVEDERECHA
        {
          PRINT_RULE("<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }", 22);

          if(( _sgeneric = st_searchCurrentScope(st, $1.lexeme)) == NULL )
          {
            EXITFAIL("Fatal error. Function identifier %s not found! ", $1.lexeme);
          }

          if ( !has_return )
          {
            EXITFAIL("Fatal error. Function does not have return st");
          }

          if ( !stopLocalScope(st) )
          {
            EXITFAIL("Fatal error, %s's scope coulnd't be closed.", $1.lexeme);
          }

          if (( _sgeneric = st_searchCurrentScope(st, $1.lexeme)) == NULL)
          {
            EXITFAIL("Fatal error. Function identifier %s not in global scope", $1.lexeme );
          }

          symbol_configure_function(
            _sgeneric,
            current_params,
            current_localvars,
            $1.type
          );

          printf("Function vars: %d\n", current_localvars);
          printf("Function params: %d\n", current_params);
          printf("Function name: %s\n", $1.lexeme );

          $$.type = $1.type; // propagate function return type
          strcpy($$.lexeme, $1.lexeme); // propagate function name

          // printf("Function vars: %d\n", current_localvars);
          // printf("Function params: %d\n", current_params);

          // write_function_declare( FPASM_NAME, $1.lexeme, current_localvars ); // function init
        }
        ;

fer1: /* function empty rule -> write function localvars */
    {
      // if( current_scope == LOCAL )
      // {
      //   current_localvars++;
      //   write_local_var( FPASM_NAME, current_var_pos );
      // }

      // for ( i = current_params - 1; i >= 0; i--)
      // {
      //   write_param( FPASM_NAME, i, current_params );
      //   // write_stack_assign_dest( FPASM_NAME, true );
      // }

      fprintf(fpasm, "\t; hola . %d\n", current_params);
      
      for( i = current_localvars; i > 0; i--)
      {
        write_local_var( FPASM_NAME, i );
      }
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 22_B                      */
/*------------------------------------------------------*/
fn_name: TOK_FUNCTION type TOK_IDENTIFICADOR
      {
        if(( _sgeneric = st_searchCurrentScope(st, $3.lexeme)) != NULL )
        {
          EXITFAIL("Identifier %s already exist. ", $3.lexeme);
        }
        if ( !declareFunction( st, $3.lexeme, $2.type, $3.int_value) )
        {
          EXITFAIL("Function %s couldn't be declared. ", $3.lexeme );
        }
        current_localvars = 0;
        current_var_pos = 1;
        current_params = 0;
        current_param_pos = 0;
        current_scope = LOCAL;
        has_return = false;

        _funct = st_searchCurrentScope( st, $3.lexeme );

        $$.type = $2.type; // propagate function return type
        strcpy($$.lexeme, $3.lexeme); // propagate function name
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 22_C                      */
/*------------------------------------------------------*/
fn_declarations: fn_name TOK_PARENTESISIZQUIERDO function_params TOK_PARENTESISDERECHO
              {
                if(( _sgeneric = st_searchCurrentScope(st, $1.lexeme )) == NULL )
                {
                  EXITFAIL("Fatal error. Function identifier %s not found", $1.lexeme);
                }

                symbol_configure_function(
                  _sgeneric,
                  current_params,
                  current_localvars,
                  $1.type
                );

                $$.type = $1.type; // propagate function return type
                strcpy($$.lexeme, $1.lexeme); // propagate function name

                // write_function_declare( FPASM_NAME, $1.lexeme, current_localvars ); // function init
              }
              ;

fer2: fn_declarations TOK_LLAVEIZQUIERDA function_declarations
    {
      write_function_declare( FPASM_NAME, $1.lexeme, current_localvars ); // function init
      fprintf(FPASM_NAME, "\t; -_-_- \n");
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
function_param: type function_param_identifier
              {
                PRINT_RULE("<parametro_funcion> ::= <tipo> <identificador>", 27);

                st_set_scalar_parametre( st, $2.lexeme, $1.type, current_param_pos++);
                current_params++;
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 27_B                      */
/*------------------------------------------------------*/
function_param_identifier: TOK_IDENTIFICADOR
                        {
                          if ((_sgeneric = st_searchCurrentScope(st, $1.lexeme)) != NULL)
                          {
                            EXITFAIL("Function param identifier exists in current scope.");
                          }

                          strcpy($$.lexeme, $1.lexeme);
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
                has_return = true;
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
assignment: TOK_IDENTIFICADOR TOK_ASIGNACION exp
    {
      PRINT_RULE("<asignacion> ::= <identificador> = <exp>", 43);
      if((_sgeneric = st_searchCurrentScope(st, $1.lexeme)) == NULL)
      {
        /* Symbol is not declared */
        EXITFAIL("Identifier %s not declared.", $1.lexeme);
      }
      if(symbol_get_category(_sgeneric) == FUNCT)
      {
        EXITFAIL("Identifier %s is a function.", $1.lexeme);
      }
      else if(symbol_blind_identifierCategory(_sgeneric) == VECTOR)
      {
        EXITFAIL("Identifier %s is a vector.", $1.lexeme);
      }  
      else if(symbol_blind_dataType(_sgeneric) != $3.type)
      {
        EXITFAIL("Identifiers type missmatch")
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
            if ( $1.type != $3.type )
            {
              EXITFAIL("Invalid assignment. 1st type != 3rd type");
            }
            _sleft = st_searchCurrentScope( st, $1.lexeme );
            if ( _sleft == NULL )
            {
              EXITFAIL("Invalid assignment. Vector does not exist");
            }
            write_stack_assign_dest( FPASM_NAME, $3.is_var );
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 48                        */
/*------------------------------------------------------*/
vector_element: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
              {
                PRINT_RULE("<elemento_vector> ::= <identificador> [ <exp> ]", 48);
                if ( ( _sleft = st_searchCurrentScope(st, $1.lexeme ) ) == NULL )
                {
                  EXITFAIL("Indexing to undeclared vector");
                }
                if ( symbol_blind_identifierCategory( _sleft ) != VECTOR )
                {
                  EXITFAIL("Trying to index %s -> ¡It's not a vector!", $1.lexeme );
                }
                else if ( $3.type != INT )
                {
                  EXITFAIL("Vector integer must be a integer"); // This is protected by assembly write_index_vector routine
                }
                $$.type = symbol_blind_dataType( _sleft );
                $$.is_var = true;
                strncpy($$.lexeme, $1.lexeme, MAX_LEN);

                // write_operand( FPASM_NAME, )
                write_index_vector( FPASM_NAME, $1.lexeme, symbol_blind_size( _sleft ), $3.is_var );
                // write_operand( FPASM_NAME, $1.lexeme, true );

              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 50                        */
/*------------------------------------------------------*/
conditional: if_exp_stm
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", 50);
            $$.tags = $1.tags;
            write_ifthenelse_end(FPASM_NAME, $$.tags);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 51                        */
/*------------------------------------------------------*/
conditional: if_exp_stm TOK_ELSE TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", 51);
            $$.tags = $1.tags;
            write_ifthenelse_end(FPASM_NAME, $$.tags);
          }
          ;

if_exp_stm: if_exp statements TOK_LLAVEDERECHA
          {
            $$.tags = $1.tags;
            write_ifthenelse_middle(FPASM_NAME, $$.tags);
          }
          ;

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA
      {
        if( $3.type != BOOLEAN)
        {
          EXITFAIL("Type missmatch. 'IF' requires boolean exp");
        }
        $$.tags = tags++;
        write_ifthenelse_begin(FPASM_NAME, $3.is_var, $$.tags);
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 52                        */
/*------------------------------------------------------*/
loop: while_exp TOK_LLAVEIZQUIERDA statements TOK_LLAVEDERECHA
    {
      PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", 52);
      $$.tags = $1.tags;
      write_while_end( FPASM_NAME, $$.tags );
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 52_B                      */
/*------------------------------------------------------*/
while_exp: while 
            TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
        {
          if ( $3.type != BOOLEAN )
          {
            EXITFAIL("Type missmatch. 'While' requires boolean as condition");
          }
          $$.tags = $1.tags;
          write_while_exp( FPASM_NAME, $3.is_var, $$.tags );
        }
        ;

/*------------------------------------------------------*/
/*                      PROD: 52_C                      */
/*------------------------------------------------------*/
while: TOK_WHILE
    {
      $$.tags = tags++;
      write_while_begin( FPASM_NAME, $$.tags );
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
          EXITFAIL("Identifier not found");
        }
        if(symbol_get_category(_sgeneric) == FUNCT)
        {
          EXITFAIL("Trying to print a function");
        }
        else if(symbol_blind_identifierCategory(_sgeneric) == VECTOR)
        {
          EXITFAIL("Trying to print a vector");
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
        printf("\n\t@@@@ %s \t %d\n", $2.lexeme, $2.is_var );
        write_function_return( FPASM_NAME, $2.is_var );
        current_scope = GLOBAL;
        _funct = NULL;
      }
      ;

/*------------------------------------------------------*/
/*                      PROD: 72                        */
/*------------------------------------------------------*/
exp: exp TOK_MAS exp
    {
      PRINT_RULE("<exp> ::= <exp> + <exp>", 72);
      if($1.type != $3.type || $1.type != INT )
      {
        EXITFAIL("Types missmatch");
      }

      write_sum(FPASM_NAME, $1.is_var, $3.is_var);
      $$.type = $1.type; // also $$.type = $3.type
      $$.is_var = false;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 73                        */
/*------------------------------------------------------*/
exp: exp TOK_MENOS exp
    {
      PRINT_RULE("<exp> ::= <exp> - <exp>", 73);
      if( $1.type != $3.type || $1.type != INT )
      {
        EXITFAIL("Substract requires both values to be the same");
      }

      write_subtract( FPASM_NAME, $1.is_var, $3.is_var );
      $$.is_var = false;
      $$.type = INT;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 74                        */
/*------------------------------------------------------*/
exp: exp TOK_DIVISION exp
    {
      PRINT_RULE("<exp> ::= <exp> / <exp>", 74);
      if( $1.type != $3.type || ($1.type != INT) )
      {
        EXITFAIL("Division requires both values to be integers");
      }
      write_div( FPASM_NAME, $1.is_var, $3.is_var );
      $$.is_var = false;
      $$.type = INT;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 75                        */
/*------------------------------------------------------*/
exp: exp TOK_ASTERISCO exp
    {
      PRINT_RULE("<exp> ::= <exp> * <exp>", 75);
      if( $1.type != $3.type || ($1.type != INT) )
      {
        EXITFAIL("Mult requires both values to be integers");
      }
      write_mult( FPASM_NAME, $1.is_var, $3.is_var );
      $$.is_var = false;
      $$.type = INT;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 76                        */
/*------------------------------------------------------*/
exp: TOK_MENOS exp %prec MENOSU
    {
      PRINT_RULE("<exp> ::= - <exp>", 76);
      if($2.type != INT)
      {
        EXITFAIL("Types missmatch. - <exp> requires integer value");
      }

      write_sign_change( FPASM_NAME, $2.is_var );
      $$.is_var = false;
      $$.type = INT;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 77                        */
/*------------------------------------------------------*/
exp: exp TOK_AND exp
    {
      PRINT_RULE("<exp> ::= <exp> && <exp>", 77);
      if( $1.type != $3.type || ($1.type != BOOLEAN) )
      {
        EXITFAIL("AND requires both values to be booleans");
      }
      write_and( FPASM_NAME, $1.is_var, $3.is_var );
      $$.is_var = false;
      $$.type = BOOLEAN;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 78                        */
/*------------------------------------------------------*/
exp: exp TOK_OR exp
    {
      PRINT_RULE("<exp> ::= <exp> || <exp>", 78);
      if( $1.type != $3.type || ($1.type != BOOLEAN) )
      {
        EXITFAIL("OR requires both values to be booleans");
      }
      write_or( FPASM_NAME, $1.is_var, $3.is_var );
      $$.is_var = false;
      $$.type = BOOLEAN;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 79                        */
/*------------------------------------------------------*/
exp: TOK_NOT exp
    {
      PRINT_RULE("<exp> ::= ! <exp>", 79);
      if( $2.type != BOOLEAN )
      {
        EXITFAIL("NOT requires value to be boolean");
      }
      write_not( FPASM_NAME, $2.is_var );
      $$.is_var = false;
      $$.type = BOOLEAN;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 80                        */
/*------------------------------------------------------*/
exp: TOK_IDENTIFICADOR
    {
      
      PRINT_RULE("<exp> ::= <identificador>", 80);
      if((_sgeneric = st_searchCurrentScope(st, $1.lexeme)) == NULL)
      {
        if ( in_fn_call )
          break;
        EXITFAIL("Identifier %s doesn't exists", $1.lexeme);
      }
      
      if(symbol_get_category(_sgeneric) == FUNCT)
      {
        EXITFAIL("Identifier %s is a function", $1.lexeme);
      }
      else if(symbol_blind_identifierCategory(_sgeneric) == VECTOR)
      {
        EXITFAIL("Identifier %s is a vector", $1.lexeme);
      }

      $$.type = symbol_blind_dataType(_sgeneric);
      $$.is_var = true;

      // if ( in_fn_call )
      // {
      //   write_stack_optoarg( FPASM_NAME, $$.is_var );
      // }

      // if ( symbol_get_category( _sgeneric ) == PARAM )
      // {
      //   printf("\tIt's a param\n");
      //   write_stack_optoarg( FPASM_NAME, $$.is_var );
      // }
      // else
      // {
      // }
      // printf("\n\tIn function call : %s\n", in_fn_call ? "yes" : "no");
      
      if ( current_scope == GLOBAL )
      {
        write_operand(FPASM_NAME, $1.lexeme, $$.is_var);
        if ( in_fn_call )
        {
          write_stack_optoarg( FPASM_NAME, $$.is_var );
        }
      }
      else
      {
        // printf("\n\tIn %s\tTotal params: %d\n", symbol_get_key(_funct), symbol_get_funct_params(_funct));
        write_param( FPASM_NAME, symbol_get_param_pos( _sgeneric ),
                      symbol_get_funct_params( _funct ) );
      }
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
      // printf("\n\tIn function call : %s\n", in_fn_call ? "yes" : "no");
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 82                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= ( <exp> )", 82);
      $$.type = $2.type;
      $$.is_var = $2.is_var;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 83                        */
/*------------------------------------------------------*/
exp: TOK_PARENTESISIZQUIERDO comparison TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= ( <comparacion> )", 83);
      $$.type = $2.type;
      $$.is_var = $2.is_var;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 85                        */
/*------------------------------------------------------*/
exp: vector_element
    {
      PRINT_RULE("<exp> ::= <elemento_vector>", 85);
      $$.type = $1.type;
      $$.is_var = $1.is_var;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 88                        */
/*------------------------------------------------------*/
exp: fidf_funct_call TOK_PARENTESISIZQUIERDO exp_list TOK_PARENTESISDERECHO
    {
      PRINT_RULE("<exp> ::= <identificador> ( <lista_expresiones> )", 88);
      if ((_funct = st_searchCurrentScope( st, $1.lexeme )) == NULL)
      {
        EXITFAIL("function called doesn't exist");
      }
      if ( symbol_get_category( _funct ) != FUNCT )
      {
        EXITFAIL("identifier called is not a function");
      }
      if ( symbol_get_funct_params( _funct ) != current_call_param_count )
      {
        EXITFAIL("function call err: %d arguments missmatch. Expected %d args\n",
                    symbol_get_funct_params( _funct ), current_call_param_count );
      }
      write_function_call( FPASM_NAME, $1.lexeme, symbol_get_funct_params( _funct ) );
      
      in_expList = false;
      $$.type = symbol_get_funct_returnType( _funct );
      $$.is_var = false;
      in_fn_call = false;
    }
    ;

/*------------------------------------------------------*/
/*                      PROD: 88_B                      */
/*------------------------------------------------------*/
fidf_funct_call: TOK_IDENTIFICADOR
              {
                if ((_sgeneric = st_searchCurrentScope( st, $1.lexeme )) == NULL)
                {
                  EXITFAIL("function called doesn't exist");
                }
                if ( symbol_get_category( _sgeneric ) != FUNCT )
                {
                  EXITFAIL("identifier called is not a function");
                }
                if ( in_expList )
                {
                  // EXITFAIL("function call inside a function call");
                }
                else
                {
                  current_call_param_count = 0;
                  in_expList = true;
                }
                in_fn_call = true;
                strncpy($$.lexeme, $1.lexeme, MAX_LEN);
              }
              ;

/*------------------------------------------------------*/
/*                      PROD: 89                        */
/*------------------------------------------------------*/
exp_list: exp exp_remaining_list
        {
          PRINT_RULE("<lista_expresiones> ::= <exp> <resto_lista_expresiones>", 89);
          // write_stack_optoarg( FPASM_NAME, $1.is_var );
          current_call_param_count++;
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
                    // write_stack_optoarg( FPASM_NAME, $2.is_var );
                    current_call_param_count++;
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
            if($1.type != INT || $1.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required.");
            }
            
            write_equal(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 94                        */
/*------------------------------------------------------*/
comparison: exp TOK_DISTINTO exp
          {
            PRINT_RULE("<comparacion> ::= <exp> != <exp>", 94);
            if($1.type != INT || $3.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            write_different(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 95                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENORIGUAL exp
          {
            PRINT_RULE("<comparacion> ::= <exp> <= <exp>", 95);
            if($1.type != INT || $3.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            
            write_lower_equal(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 96                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYORIGUAL exp
          {
            PRINT_RULE("<comparacion> ::= <exp> >= <exp>", 96);
            if($1.type != INT || $3.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }

            write_greater_equal(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 97                        */
/*------------------------------------------------------*/
comparison: exp TOK_MENOR exp
          {
            PRINT_RULE("<comparacion> ::= <exp> < <exp>", 97);
            if($1.type != INT || $3.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            
            write_lower(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 98                        */
/*------------------------------------------------------*/
comparison: exp TOK_MAYOR exp
          {
            PRINT_RULE("<comparacion> ::= <exp> > <exp>", 98);
            if($1.type != INT || $3.type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }

            write_greater(FPASM_NAME, $1.is_var, $3.is_var, tags++);
            $$.type = BOOLEAN;
            $$.is_var = false;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 99                        */
/*------------------------------------------------------*/
constant: constant_logic
          {
            PRINT_RULE("<constante> ::= <constante_logica>", 99);
            $$.type = $1.type;
            $$.is_var = $1.is_var;
            /* push */
            snprintf( __buff, MAX_LEN, "%d", $1.bool_value );
            write_operand( FPASM_NAME, __buff, false );
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
            /* push */
            snprintf(__buff, MAX_LEN, "%d", $1.int_value);
            write_operand(FPASM_NAME, __buff, false);
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 102                       */
/*------------------------------------------------------*/
constant_logic: TOK_TRUE
          {
            PRINT_RULE("<constante_logica> ::= true", 102);
            $$.type = BOOLEAN;
            $$.is_var = false;
            $$.bool_value = true;
          }
          ;

/*------------------------------------------------------*/
/*                      PROD: 103                       */
/*------------------------------------------------------*/
constant_logic: TOK_FALSE
          {
            PRINT_RULE("<constante_logica> ::= false", 103);
            $$.type = BOOLEAN;
            $$.is_var = false;
            $$.bool_value = false;
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
            }
            ;

/*------------------------------------------------------*/
/*                      PROD: 108                       */
/*------------------------------------------------------*/
identifier: TOK_IDENTIFICADOR
          {
            PRINT_RULE("<identificador> ::= TOK_IDENTIFICADOR", 108);
            if((_sgeneric = st_searchCurrentScope(st, $1.lexeme)) != NULL)
            {
              EXITFAIL("Identifier %s already at %s scope", $1.lexeme, current_scope == GLOBAL ? "global" : "local");
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
                current_param_pos,
                current_var_pos,
                current_vector_size,
                current_params,
                current_localvars
              );
              
              if( current_scope == LOCAL )
              {
                current_localvars++;
                // write_local_var( FPASM_NAME, current_var_pos );
              }
              // else
              // {
              //   EXITFAIL("Failure in insertion of %s identifier in %s scope.\n",
              //               $1.lexeme, current_scope == GLOBAL ? "global" : "local");
              // }
            }
          }
          ;

%%

/* User functions definitions */

int yyerror(SymbolsTable *st, char *s)
{
  if(morfofailure)
  {
    return PARSEFAIL;
  }
  
  COPYERR("Syntactic error: %s", s);
  
  return PARSEFAIL;
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