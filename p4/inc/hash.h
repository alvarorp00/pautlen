#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "alfa.h"
#include "symbol.h"

#define _DEF_HASHLEN_ 15
#define _CRITICAL_FACTOR_ 0.7

typedef uint_fast64_t (*Hashcode)(void*);
typedef bool (*Equals)(void*, void*);
typedef void (*Clean)(void*);

typedef struct _Hash Hash;

Hash *hash_init(Hashcode hashcode, Equals equals, Clean clean);
bool hash_encode(Hash *hash, void *value);
void *hash_decode(Hash *hash, void *value);
bool hash_deleteValue(Hash *hash, void* value);
void hash_clean(Hash *hash);
bool hash_contains(Hash *hash, void *value);

#endif