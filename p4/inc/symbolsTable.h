#ifndef _SYMBOLS_TABLE_H
#define _SYMBOLS_TABLE_H

typedef struct _SymbolsTable SymbolsTable;

SymbolsTable *symbolsTableInit();

void symbolsTableClean(SymbolsTable *self);

#endif