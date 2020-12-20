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

DataType symbol_blind_dataType(symbol_t *s);

IdentifierCategory symbol_blind_identifierCategory(symbol_t *s);

int8_t symbol_blind_size(symbol_t *s);

Scope symbol_blind_scope(symbol_t *s);

/*- - - VARS - - - */

DataType symbol_get_var_dataType(symbol_t *s);

IdentifierCategory symbol_get_var_identifierCategory(symbol_t *s);

Scope symbol_get_var_scope(symbol_t *s);

int symbol_get_var_pos(symbol_t *s);

int8_t symbol_get_var_size(symbol_t *s);

/* - - - PARAMS - - -  */

DataType symbol_get_param_dataType(symbol_t *s);

IdentifierCategory symbol_get_param_identifierCategory(symbol_t *s);

int symbol_get_param_pos(symbol_t *s);

int8_t symbol_get_param_size(symbol_t *s);

/* - - - FUNCTS - - - */

int32_t symbol_get_funct_params(symbol_t *s);

int32_t symbol_get_funct_localvars(symbol_t *s);

DataType symbol_get_funct_returnType(symbol_t *s);

/*  - * - * - * - * - * - * - * - */

#endif
