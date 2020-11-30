#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define _DEF_HASHLEN_ 22500

#define _KEY_MAX_SIZE_ 128

#define _VECTOR_MAX_LEN_ 64
#define _VECTOR_MIN_LEN_ 1

enum _ElementCategory
{
  VAR,
  PARAM,
  FUNCT
};

enum _DataType
{
  BOOLEAN,
  INT
};

enum _IdentifierCategory
{
  SCALAR,
  VECTOR
};

enum _Scope
{
  GLOBAL,
  LOCAL
};

typedef enum _ElementCategory ElementCategory;
typedef enum _DataType DataType;
typedef enum _IdentifierCategory IdentifierCategory;
typedef enum _Scope Scope;

typedef struct _Hash Hash;
typedef char* String;

Hash *hash_init();

bool hash_encode(Hash *self, String identifier);

void *hash_decode(Hash *self, String identifier);

void hash_clean(Hash *self);

#endif