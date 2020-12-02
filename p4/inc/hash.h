#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "alfa.h"
#include "symbol.h"

#define _DEF_HASHLEN_ 22500

typedef size_t (*Hashcode)(void*);
typedef bool (*Equals)(void*, void*);
typedef void (*Clean)(void*);

typedef struct _Hash Hash;

Hash *hash_init(Hashcode hashcode, Equals equals, Clean clean);

bool hash_encode(Hash *hash, void *value);

void *hash_decode(Hash *hash, void *value);
void hash_clean(Hash *hash);
bool hash_contains(Hash *hash, void *value);

#endif