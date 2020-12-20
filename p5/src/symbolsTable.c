/**
 * 
 * HEADER 
 * 
 */

#include "symbolsTable.h"

struct _SymbolsTable
{
  hash_t *globalScope; /* Used for global identifiers */
  hash_t *localScope; /* Used for local identifiers */
  Scope currentScope; /* Access quickly to current scope */
};

/* Helper functions */

/**
 * Searchs a symbol in given hash
 * @param hash where to search
 * @param identifier of symbol to search
 * @return symbol found or NULL
 */
static symbol_t *searchSymbol(hash_t *hash, String identifier);

/* ---------------- */

SymbolsTable *symbolsTableInit()
{
  SymbolsTable *symbolsTable;

  symbolsTable = (SymbolsTable*)calloc(1, sizeof(SymbolsTable));
  if(!symbolsTable)
    return NULL;

  symbolsTable->globalScope = hash_init(
    (hashcode_t)symbol_hashcode,
    (equals_t)symbol_equals,
    (clean_t)symbol_delete
  );

  if(!symbolsTable->globalScope)
  {
    symbolsTableClean(symbolsTable);
  }

  symbolsTable->currentScope = GLOBAL;

  return symbolsTable;
}

void symbolsTableClean(SymbolsTable *st)
{
  if(!st)
    return;

  if(st->globalScope != NULL)
    hash_clean(st->globalScope);

  if(st->currentScope == LOCAL)
    hash_clean(st->localScope);
  
  free(st);

  return;
}

/* -------------------------------------------- */

bool declareGlobal(SymbolsTable *st, String identifier, int value)
{
  symbol_t *s;

  // if(value < 0)
  //   return declareFunction(st, identifier, value);
  
  if(!st || !identifier)
    return false;
  if(st->currentScope != GLOBAL)
    return false;
  
  if (searchSymbol(st->globalScope, identifier) != NULL)
    return false;
  
  s = symbol_init(identifier, value);

  if(!s)
    return false;  

  return hash_encode(st->globalScope, s);;
}

bool declareLocal(SymbolsTable *st, String identifier, int value)
{
  symbol_t *s;
  
  if(!st || !identifier || value < 0)
    return false;
  if(st->currentScope != LOCAL)
    return false;

  if (searchSymbol(st->localScope, identifier) != NULL)
    return false;
  
  s = symbol_init(identifier, value);

  if(!s)
    return false;

  return hash_encode(st->localScope, s);
}

symbol_t* globalUse(SymbolsTable *st, String identifier)
{  
  if(!st || !identifier)
    return NULL;

  return searchSymbol(st->globalScope, identifier);
}

symbol_t* localUse(SymbolsTable *st, String identifier)
{
  symbol_t *s;
  
  if(!st || !identifier)
    return NULL;

  if(st->currentScope != LOCAL)
    return NULL;

  if((s = searchSymbol(st->localScope, identifier)) != NULL)
    return s;

  return searchSymbol(st->globalScope, identifier); 
}

symbol_t* findExclusiveLocal(SymbolsTable *st, String identifier)
{ 
  if(!st || !identifier)
    return NULL;

  if(st->currentScope != LOCAL)
    return NULL;

  return searchSymbol(st->localScope, identifier);
}

bool declareFunction(SymbolsTable *st, String identifier, DataType returnType ,int value)
{
  symbol_t *s;
  
  if(!st || !identifier )
    return false;
  if(searchSymbol(st->globalScope, identifier) != NULL)
    return false;
  
  s = symbol_init(identifier, value);
    
  if(!hash_encode(st->globalScope, s))
    return false;
  
  st->localScope = hash_init(
    (hashcode_t)symbol_hashcode,
    (equals_t)symbol_equals,
    (clean_t)symbol_delete
  );

  if(!st->localScope)
    return false;

  s = symbol_init(identifier, value); /* Start other again */
  
  if(!hash_encode(st->localScope, s))
    return false;
  
  st->currentScope = LOCAL;

  return true;
}

bool stopLocalScope(SymbolsTable *st)
{
  if(!st || st->currentScope != LOCAL)
    return false;

  if(!st->localScope)
    return false;

  hash_clean(st->localScope);

  st->currentScope = GLOBAL;

  return true;
}

/* -------------------------------------------- */

symbol_t* st_searchCurrentScope(SymbolsTable *st, String identifier)
{
  if(!st || !identifier)
    return NULL;
  // return searchSymbol(
  //   st->currentScope == GLOBAL ? st->globalScope : st->localScope,
  //   identifier
  // );
  return st->currentScope == GLOBAL ? 
    globalUse(st, identifier) : localUse(st, identifier);
}

/* -------------------------------------------- */

bool st_set_scalar_variable(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  Scope scope,
  int pos
)
{
  symbol_t *s;
  hash_t *dst;
  
  if(!st || !identifier)
    return false;

  if(scope == LOCAL && st->currentScope != LOCAL)
    return false;
  else if(scope == GLOBAL && st->currentScope != GLOBAL)
    return false;
  
  dst = (scope == GLOBAL) ? st->globalScope : st->localScope;

  if((s = searchSymbol(dst, identifier)) != NULL)
    return false;

  s = symbol_init(identifier, NONE);
  symbol_configure_scalar_variable(s, dt, scope, scope == LOCAL ? pos : NONE);
  hash_encode(dst, s);

  return true;
}

bool st_set_vector_variable(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  Scope scope,
  int pos,
  int8_t size
)
{
  symbol_t *s;
  hash_t *dst;
  
  if(!st || !identifier || !size )
    return false;

  if(scope == LOCAL && st->currentScope != LOCAL)
    return false;
  else if(scope == GLOBAL && st->currentScope != GLOBAL)
    return false;
  
  dst = (scope == GLOBAL) ? st->globalScope : st->localScope;

  if((s = searchSymbol(dst, identifier)) != NULL)
    return false;

  s = symbol_init(identifier, NONE);
  symbol_configure_vector_variable(s, dt, scope, scope == LOCAL ? pos : NONE, size);
  
  return hash_encode(dst, s);
}

bool st_set_scalar_parametre(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  int pos
)
{
  symbol_t *s;
  
  if(!st || !identifier)
    return false;

  if(st->currentScope != LOCAL)
    return false;

  if((s = searchSymbol(st->localScope, identifier)) != NULL)
    return false;

  s = symbol_init(identifier, NONE);

  symbol_configure_scalar_parametre(s, dt, pos);

  return hash_encode(st->localScope, s);;
}

bool st_set_vector_parametre(
  SymbolsTable *st,
  String identifier,
  DataType dt,
  int pos,
  int8_t size
)
{
  symbol_t *s;
  
  if(!st || !identifier)
    return false;

  if(st->currentScope != LOCAL)
    return false;
  
  if((s = searchSymbol(st->localScope, identifier)) != NULL)
    return false;

  s = symbol_init(identifier, NONE);
  symbol_configure_vector_parametre(s, dt, pos, size);

  return hash_encode(st->localScope, s);
}

bool st_set_function(
  SymbolsTable *st,
  String identifier,
  int32_t params,
  int32_t localvars,
  DataType returnType
)
{
  symbol_t *s;
  
  if(!st || !identifier)
    return false;

  if(st->currentScope != GLOBAL)
    return false;

  if((s = searchSymbol(st->globalScope, identifier)) != NULL)
    return false;

  s = symbol_init(identifier, NONE);
  symbol_configure_function(s, params, localvars, returnType);

  return hash_encode(st->localScope, s);
}

/* ------------------------------------------- */

Scope st_getScope(SymbolsTable *st)
{
  if(!st)
    return UNSP_ERR;

  return st->currentScope;
}

/* -------------------------------------------- */

static symbol_t* searchSymbol(hash_t *hash, String identifier)
{
  symbol_t *tmp, *_tmp;
  
  if(!hash || !identifier)
    return NULL;

  tmp = symbol_init(identifier, NONE);
  _tmp = (symbol_t*)hash_decode(hash, tmp);

  symbol_delete(tmp);

  return _tmp;
}

/* -------------------------------------------- */

bool st_insertBlindCurrentScope(
  SymbolsTable *st,
  String identifier,
  ElementCategory elemCat,
  DataType dataType,
  IdentifierCategory identifierCategory,
  Scope scope,
  int32_t param_pos,
  int32_t var_pos,
  int8_t size,
  int32_t params,
  int32_t localvars
)
{
  hash_t *dst;
  
  if(!st || !identifier)
    return false;

  if(scope != st->currentScope)
    return false;
  
  dst = st->currentScope == GLOBAL ? st->globalScope : st->localScope;
    
  if(searchSymbol(dst, identifier) != NULL)
    return false;
  
  switch (elemCat)
  {
  case VAR:

    switch (identifierCategory)
    {
    case SCALAR:
      return st_set_scalar_variable(
        st,
        identifier,
        dataType,
        scope,
        var_pos
      );

    case VECTOR:
      return st_set_vector_variable(
        st,
        identifier,
        dataType,
        scope,
        var_pos,
        size
      );
    
    default:
      return false;
    }
    
    break;
  
  case PARAM:
    switch (identifierCategory)
    {
    case SCALAR:
      return st_set_scalar_parametre(
        st,
        identifier,
        dataType,
        param_pos
      );

    case VECTOR:
      return st_set_vector_parametre(
        st,
        identifier,
        dataType,
        param_pos,
        size
      );
    
    default:
      return false;
    }
    break;

  case FUNCT:
    return st_set_function(
      st,
      identifier,
      params,
      localvars,
      dataType
    );

  default:
    return false;
  }
}

/* -------------------------------------------- */

hash_t *st_getScopeHash(SymbolsTable *st)
{
  if(!st)
    return NULL;
  return st->currentScope == GLOBAL ? st->globalScope : st->localScope;
}