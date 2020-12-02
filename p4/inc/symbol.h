#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdint.h>
#include "alfa.h"

typedef struct _Variable Variable;
typedef struct _Parametre Parametre;
typedef struct _Function Function;

typedef union _Element Element;
typedef union _Data Data;

/**
 * Starts a new symbol_init structure
 */
Symbol* symbol_init(String key, int value);

/**
 * 
 */
void symbol_set_category(Symbol *s, ElementCategory elemCat);

/**
 * 
 */
ElementCategory symbol_get_category(Symbol *s);

/**
 * Returns symbol's key (String)
 */
String symbol_get_key(Symbol *sn);

/**
 * Sets symbol's key
 */
bool symbol_set_key(Symbol *sn, String key);

/**
 * Configures symbol as a scalar variable
 */
void symbol_configure_scalar_variable(Symbol *sn, DataType basicType, Scope scope, uint_fast16_t pos);

/**
 * Configures symbol as a vector variable
 */
void symbol_configure_vector_variable(Symbol *sn, DataType basictype, Scope scope, uint_fast16_t pos, uint_fast16_t size);

/**
 * Configures symbol as a scalar parametre
 */
void symbol_configure_scalar_parametre(Symbol *sn, DataType basicType, uint_fast16_t pos);

/**
 * Configures symbol as a vector parametre
 */
void symbol_configure_vector_parametre(Symbol *sn, DataType basicType, uint_fast16_t pos, uint_fast16_t size);

/**
 * Configure Function
 */
void symbol_configure_function(Symbol *sn, uint_fast16_t params, uint_fast16_t localvars);

/**
 * Return true if both symbols are equal
 */
bool symbol_equals(Symbol *s1, Symbol *s2);

/**
 * Hashcode funct
 */
uint_fast64_t symbol_hashcode(void *s);

/**
 * Cleans symbol
 */
void symbol_delete(void *s);

#endif
