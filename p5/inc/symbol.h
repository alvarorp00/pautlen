#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdint.h>
#include "alfa.h"

/**
 * Variable type definition
 */
typedef struct _Variable Variable;

/**
 * Parametre type definition
 */
typedef struct _Parametre Parametre;

/**
 * Function type definition
 */
typedef struct _Function Function;

/**
 * union with element stored
 */
typedef union _Element Element;

/**
 * Initializes a new Symbol
 * @param key identifier
 * @param value value assigned
 * @return new symbol
 */
Symbol* symbol_init(String key, int value);

/**
 * Set symbol's element category
 * @param s symbol
 * @param elemCat category to insert {VAR, PARAM, FUNC}
 */
void symbol_set_category(Symbol *s, ElementCategory elemCat);

/**
 * Get symbol's category
 * @param s symbol
 * @return category of the symbol
 */
ElementCategory symbol_get_category(Symbol *s);

/**
 * Retrieves symbol's key
 * @param s symbol
 * @return Array with symbol's key
 */
String symbol_get_key(Symbol *s);

/**
 * Get symbol's value
 * @param s symbol
 * @return symbol's value
 */
int symbol_get_value(Symbol *s);

/**
 * Configures symbol as an scalar variable
 * @param s symbol
 * @param dataType type {BOOLEAN, INT}
 * @param scope scope {LOCAL, GLOBAL}
 * @param pos position in case it's in a function
 */
void symbol_configure_scalar_variable(
  Symbol *s,
  DataType dataType,
  Scope scope,
  int pos
);

/**
 * Configures symbol as an vector variable
 * @param s symbol
 * @param dataType type {BOOLEAN, INT}
 * @param scope scope {LOCAL, GLOBAL}
 * @param pos position in case it's in a function
 * @param size size of the vector
 */
void symbol_configure_vector_variable(
  Symbol *s,
  DataType dataType,
  Scope scope,
  int pos,
  int8_t size
);

/**
 * Configures symbol as an scalar parametre
 * @param s symbol
 * @param dataType type {BOOLEAN, INT}
 * @param pos position in function arguments, start in 0
 */
void symbol_configure_scalar_parametre(
  Symbol *s,
  DataType dataType,
  int pos
);

/**
 * Configures symbol as an vector parametre
 * @param s symbol
 * @param dataType type {BOOLEAN, INT}
 * @param pos position in case it's in a function
 * @param size size of the vector
 */
void symbol_configure_vector_parametre(
  Symbol *s,
  DataType dataType,
  int pos,
  int8_t size
);

/**
 * Configures symbol as a function
 * @param s symbol
 * @param params number of params, starting in 0
 * @param localvars number of localvars, starting in 1
 */
void symbol_configure_function(
  Symbol *s,
  int32_t params,
  int32_t localvars,
  DataType returnType
);

/**
 * Compares two symbol's
 * @param s1 symbol1
 * @param s2 symbol2
 * @return true if equal, else false
 */
bool symbol_equals(Symbol *s1, Symbol *s2);

/**
 * Calculates hashcode for given symbol
 * @param s symbol
 * @return hashcode raw value
 */
uint_fast64_t symbol_hashcode(void *s);

/**
 * Delete's symbol
 * @param s symbol to delete
 */
void symbol_delete(void *s);

/* ------------------------------ */
/* -- -- -- - GETTERS -- -- -- -- */
/* ------------------------------ */

/* - - - COMMON - - - */

DataType symbol_blind_dataType(Symbol *s);

IdentifierCategory symbol_blind_identifierCategory(Symbol *s);

int8_t symbol_blind_size(Symbol *s);

/*- - - VARS - - - */

DataType symbol_get_var_dataType(Symbol *s);

IdentifierCategory symbol_get_var_identifierCategory(Symbol *s);

Scope symbol_get_var_scope(Symbol *s);

int symbol_get_var_pos(Symbol *s);

int8_t symbol_get_var_size(Symbol *s);

/* - - - PARAMS - - -  */

DataType symbol_get_param_dataType(Symbol *s);

IdentifierCategory symbol_get_param_identifierCategory(Symbol *s);

int symbol_get_param_pos(Symbol *s);

int8_t symbol_get_param_size(Symbol *s);

/* - - - FUNCTS - - - */

int32_t symbol_get_funct_params(Symbol *s);

int32_t symbol_get_funct_localvars(Symbol *s);

DataType symbol_get_funct_returnType(Symbol *s);

/*  - * - * - * - * - * - * - * - */

#endif
