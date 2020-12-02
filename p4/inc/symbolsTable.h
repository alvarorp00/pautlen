#ifndef _SYMBOLS_TABLE_H
#define _SYMBOLS_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct _SymbolsTable SymbolsTable;

SymbolsTable *symbolsTableInit();
void symbolsTableClean(SymbolsTable *self);

/* ------------------------------------------------ */

bool declareGlobal(SymbolsTable *st, String identifier, int value);
bool declareLocal(SymbolsTable *st, String identifier, int value);
Symbol* globalUse(SymbolsTable *st, String identifier);
Symbol* localUse(SymbolsTable *st, String identifier);
bool declareFunction(SymbolsTable *st, String identifier, int value);

/* ------------------------------------------------ */

#endif