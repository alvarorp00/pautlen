#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "tokens.h"

#define _USE_DEFAULT -1

typedef struct _Hash Hash;

Hash* hash_init(int size);
bool hash_encode(Hash *hash, int index, char* value);
char* hash_decode(Hash *hash, int index);
void hash_remove(Hash *hash, int index);
void hash_destroy(Hash *hash);

#endif