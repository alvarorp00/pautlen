/**
 * 
 * HEADER 
 * 
 */

#include "symbolsTable.h"

struct _SymbolsTable
{
  Hash *globalScope; /* Used for global identifiers */
  Hash *localScope; /* Used for local identifiers */
  Scope currentScope; /* Access quickly to current scope */
};

/* Helper functions */

static Symbol *searchSymbol(Hash *hash, String identifier);

/* ---------------- */

SymbolsTable *symbolsTableInit()
{
  SymbolsTable *symbolsTable;

  symbolsTable = (SymbolsTable*)calloc(1, sizeof(SymbolsTable));
  if(!symbolsTable)
    return NULL;

  symbolsTable->globalScope = hash_init((Hashcode)symbol_hashcode, (Equals)symbol_equals, (Clean)symbol_delete);
  if(!symbolsTable->globalScope)
  {
    symbolsTableClean(symbolsTable);
  }

  return symbolsTable;
}

void symbolsTableClean(SymbolsTable *self)
{
  if(!self)
    return;

  if(self->globalScope != NULL)
    hash_clean(self->globalScope);

  if(self->localScope != NULL)
    hash_clean(self->localScope);
  
  free(self);

  return;
}

bool declareGlobal(SymbolsTable *st, String identifier, int value)
{
  Symbol *s;
  
  if(!st || !identifier)
    return false;
  if(st->currentScope != GLOBAL)
    return false;
  
  s = symbol_init(identifier, value);

  if(!s)
    return false;

  return hash_encode(st->globalScope, s);;
}

bool declareLocal(SymbolsTable *st, String identifier, int value)
{
  Symbol *s;
  
  if(!st || !identifier)
    return false;
  if(st->currentScope != LOCAL)
    return false;
  
  s = symbol_init(identifier, value);

  if(!s)
    return false;

  return hash_encode(st->localScope, s);
}

Symbol* globalUse(SymbolsTable *st, String identifier)
{  
  if(!st || !identifier)
    return NULL;

  return searchSymbol(st->globalScope, identifier);
}

Symbol* localUse(SymbolsTable *st, String identifier)
{
  if(!st || !identifier)
    return NULL;

  return searchSymbol(st->localScope, identifier); 
}

bool declareFunction(SymbolsTable *st, String identifier, int value)
{

}

static Symbol* searchSymbol(Hash *hash, String identifier)
{
  Symbol *tmp, *_tmp;
  
  if(!hash || !identifier)
    return NULL;

  tmp = symbol_init(identifier, NONE);
  _tmp = (Symbol*)hash_decode(hash, tmp);

  symbol_delete(tmp);

  return _tmp;
}