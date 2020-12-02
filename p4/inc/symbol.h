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
Symbol* symbol_init(ElementCategory elemCat, String key);

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
void symbol_configure_scalar_variable(Symbol *sn, DataType basicType, Scope scope, __u_short pos, int value);

/**
 * Configures symbol as a vector variable
 */
void symbol_configure_vector_variable(Symbol *sn, DataType basictype, Scope scope, __u_short pos, __u_int size);

/**
 * Configures symbol as a scalar parametre
 */
void symbol_configure_scalar_parametre(Symbol *sn, DataType basicType, __u_short pos, int value);

/**
 * Configures symbol as a vector parametre
 */
void symbol_configure_vector_parametre(Symbol *sn, DataType basicType, __u_short pos, __u_int size);

/**
 * Configure Function
 */
void symbol_configure_function(Symbol *sn, __u_short params, __u_short localvars, int value);

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