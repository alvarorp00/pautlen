#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdint.h>
#include "alfa.h"

typedef struct _symbol_t symbol_t;

/**
 * Initializes a new symbol_t
 * @param key identifier
 * @param value value assigned
 * @return new symbol
 */
symbol_t* symbol_init(String key, int value);

/**
 * Set symbol's element category
 * @param s symbol
 * @param elemCat category to insert {VAR, PARAM, FUNC}
 */
void symbol_set_category(symbol_t *s, ElementCategory elemCat);

/**
 * Get symbol's category
 * @param s symbol
 * @return category of the symbol
 */
ElementCategory symbol_get_category(symbol_t *s);

/**
 * Retrieves symbol's key
 * @param s symbol
 * @return Array with symbol's key
 */
String symbol_get_key(symbol_t *s);

/**
 * Get symbol's value
 * @param s symbol
 * @return symbol's value
 */
int symbol_get_value(symbol_t *s);

/* ------------------------------ */
/* -- -- -- - SETTERS -- -- -- -- */
/* ------------------------------ */

/**
 * Configures symbol as an scalar variable
 * @param s symbol
 * @param dataType type {BOOLEAN, INT}
 * @param scope scope {LOCAL, GLOBAL}
 * @param pos position in case it's in a function
 */
void symbol_configure_scalar_variable(
  symbol_t *s,
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
  symbol_t *s,
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
  symbol_t *s,
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
  symbol_t *s,
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
  symbol_t *s,
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
bool symbol_equals(symbol_t *s1, symbol_t *s2);

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

/**
 * Gets datatype in case 
 * we don't know if it's a param
 * or a variable
 * @param s symbol
 * @return data type
 */
DataType symbol_blind_dataType(symbol_t *s);

/**
 * Gets identifier category in case
 * we don't know if it's a param
 * or a variable
 * @param s symbol
 * @return identifier category
 */
IdentifierCategory symbol_blind_identifierCategory(symbol_t *s);

/**
 * Gets size in case we don't know
 * if it's a param or a variable
 * @param s symbol
 * @return vector's size
 */
int8_t symbol_blind_size(symbol_t *s);

/**
 * Gets scope. Would be better using
 * symbol_get_var_scope(symbol_t *s) asa
 * params have LOCAL & functions no
 * @param s symbol
 * @return scope
 */
Scope symbol_blind_scope(symbol_t *s);

/*- - - VARS - - - */

/**
 * Gets var datatype
 * @param s symbol
 * @return data type
 */
DataType symbol_get_var_dataType(symbol_t *s);

/**
 * Gets var identifier category
 * @param s symbol
 * @return identifier category
 */
IdentifierCategory symbol_get_var_identifierCategory(symbol_t *s);

/**
 * Gets var scope
 * @param s symbol
 * @return scope
 */
Scope symbol_get_var_scope(symbol_t *s);

/**
 * Gets var position if it's in local scope
 * @param s symbol
 * @return pos
 */
int symbol_get_var_pos(symbol_t *s);

/**
 * Gets var size in case it's a vector
 * @param s symbol
 * @return vector's size, 0 if it's SCALAR
 */
int8_t symbol_get_var_size(symbol_t *s);

/* - - - PARAMS - - -  */

/**
 * Gets param datatype
 * @param s symbol
 * @return data type
 */
DataType symbol_get_param_dataType(symbol_t *s);

/**
 * Gets param identifier category
 * @param s
 * @return identifier category
 */
IdentifierCategory symbol_get_param_identifierCategory(symbol_t *s);

/**
 * Gets param pos inside function
 * @param s symbol
 * @return position
 */
int symbol_get_param_pos(symbol_t *s);

/**
 * Gets param size in case it's a vector,
 * either currently it's not supported
 * @param s symbol
 * @return size
 */
int8_t symbol_get_param_size(symbol_t *s);

/* - - - FUNCTS - - - */

/**
 * Gets function params qty
 * @param s symbol
 * @return number of params
 */
int32_t symbol_get_funct_params(symbol_t *s);

/**
 * Gets function localvars qty
 * @param s
 * @return number of localvars
 */
int32_t symbol_get_funct_localvars(symbol_t *s);

/**
 * Gets function return type
 * @param s symbol
 * @return data type
 */
DataType symbol_get_funct_returnType(symbol_t *s);

/*  - * - * - * - * - * - * - * - */

#endif
