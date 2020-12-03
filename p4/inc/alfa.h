#ifndef _ALFA_H_
#define _ALFA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define STR(x) #x

#define READ(file) fopen(file, "r");
#define WRITE(file) fopen(file, "w");

#define TO_STDERR(format, ...) \
            fprintf(stderr, ">>> " format ".\n", ##__VA_ARGS__)

#define TO_STDOUT(format, ...) \
            fprintf(stdout, ">>> " format ".\n", ##__VA_ARGS__)

#define BUFF 128
#define MAX_LEN 100

#define UNSP_ERR INT_MIN
#define NONE INT_MAX

#define _KEY_MAX_SIZE_ MAX_LEN

#define COPY(te, tf) \
            strncpy(te, tf, BUFF)

#define COPYERR(file, str, ...) \
            snprintf(errbuff, BUFF, "*** at %s: [at line: %d; col: %d]: " str, file, line, col, ##__VA_ARGS__);

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

typedef struct _Symbol Symbol;

typedef char* String;

extern char errbuff[BUFF];
extern bool morfofailure;

extern int line;
extern int col;

#endif