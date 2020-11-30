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

bool declareGlobal(String identifier, int value);
bool declareLocal(String identifier, int value);
SymbolNode* globalUse(String identifier);
SymbolNode* localUse(String identifier);
bool declareFunction(String identifier, int value);

/* ------------------------------------------------ */

#endif