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
};

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