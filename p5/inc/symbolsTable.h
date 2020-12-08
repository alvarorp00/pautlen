#ifndef _SYMBOLS_TABLE_H
#define _SYMBOLS_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "hash.h"

typedef struct _SymbolsTable SymbolsTable;

/**
 * Initializes a new symbolsTable
 * @return initialized structure
 */
SymbolsTable *symbolsTableInit();

/**
 * Deletes given symbolsTable
 * @param st table to clean
 */
void symbolsTableClean(SymbolsTable *st);

/* ------------------------------------------------ */

/**
 * Initializes a new symbol in global scope
 * @param st table where symbol'll be stored
 * @param identifier of the new symbol
 * @param value of the new symbol
 * @return if it was posible to do it
 */
bool declareGlobal(SymbolsTable *st, String identifier, int value);

/**
 * Initializes a new symbol in local scope
 * @param st table where symbol'll be stored
 * @param identifier of the new symbol
 * @param value of the new symbol
 * @return if it was posible to do it
 */
bool declareLocal(SymbolsTable *st, String identifier, int value);

/**
 * Search a symbol in global scope
 * @param st table where symbol is stored
 * @param identifier of the symbol to search
 * @return symbol found or NULL
 */
Symbol* globalUse(SymbolsTable *st, String identifier);

/**
 * Search a symbol in local scope
 * @param st table where symbol is stored
 * @param identifier of the symbol to search
 * @return symbol found or NULL
 */
Symbol* localUse(SymbolsTable *st, String identifier);

/**
 * Declares function and starts local scope
 * @param st table where func will be stored
 * @param identifier of the function
 * @param value of the function
 */
bool declareFunction(SymbolsTable *st, String identifier, int value);

/* ------------------------------------------------ */

Symbol* st_searchCurrentScope(SymbolsTable *st, String identifier);

/* ------------------------------------------------ */

/**
 * Set symbol as escalar variable
 * @param st table where symbol is stored
 * @param identifier of the symbol
 * @param datatype type of the symbol {INT, BOOLEAN}
 * @param scope scope of the symbol {GLOBAL, LOCAL}
 * @param pos position in case it's in local function
 * @return if it was ok
 */
bool st_set_scalar_variable(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  Scope scope,
  int pos
);

/**
 * Set symbol as vector variable
 * @param st table where symbol is stored
 * @param identifier of the symbol
 * @param datatype type of the symbol {INT, BOOLEAN}
 * @param scope scope of the symbol {GLOBAL, LOCAL}
 * @param pos position in case it's in local function
 * @param size size of the vector
 * @return if it was ok
 */
bool st_set_vector_variable(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  Scope scope,
  int pos,
  int8_t size
);

/**
 * Set symbol as escalar parametre
 * @param st table where symbol is stored
 * @param identifier of the symbol
 * @param datatype type of the symbol {INT, BOOLEAN}
 * @param pos position in case it's in local function
 * @return if it was ok
 */
bool st_set_scalar_parametre(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  int pos
);

/**
 * Set symbol as vector parametre
 * @param st table where symbol is stored
 * @param identifier of the symbol
 * @param datatype type of the symbol {INT, BOOLEAN}
 * @param pos position in case it's in local function
 * @param size size of the vector
 * @return if it was ok
 */
bool st_set_vector_parametre(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  int pos,
  int8_t size
);

/**
 * Set symbol as function
 * @param st table where symbol is stored
 * @param identifier of the symbol
 * @param params number of function params
 * @param localvars number of function localvars
 * @return if it was ok
 */
bool st_set_function(
  SymbolsTable *st,
  String identifier,
  int32_t params,
  int32_t localvars
);

/**
 * Closes local scope, sets global one
 * @param st table to set
 * @return if it was ok
 */
bool stopLocalScope(SymbolsTable *st);

/**
 * Returns current scope
 * @param st table to check
 * @return scope of the table
 */
Scope st_getScope(SymbolsTable *st);

Hash *st_getScopeHash(SymbolsTable *st);

/* ------------------------------------------------ */

bool st_insertBlindCurrentScope(
  SymbolsTable *st,
  String identifier,
  ElementCategory elemCat,
  DataType dataType,
  IdentifierCategory identifierCategory,
  Scope scope,
  int pos,
  int8_t size,
  int32_t params,
  int32_t localvars
);

#endif
