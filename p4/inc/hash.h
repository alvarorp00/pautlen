#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "alfa.h"
#include "symbolNode.h"

#define _DEF_HASHLEN_ 22500

typedef struct _Hash Hash;

Hash *hash_init();

bool hash_encode(Hash *self, SymbolNode *sn);

SymbolNode *hash_decode(Hash *self, String identifier);
void hash_clean(Hash *self);
bool hash_contains(Hash *self, String identifier);

#endif