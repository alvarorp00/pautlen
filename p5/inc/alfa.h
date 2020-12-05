#ifndef _ALFA_H_
#define _ALFA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "generator.h"

/**
 * Converts literal to string
 * @param x literal to convert
 */
#define STR(x) #x

/**
 * Opens file in read mode
 * @param file to open
 */
#define READ(file) fopen(file, "r");

/**
 * Opens file in write mode
 * @param file to open
 */
#define WRITE(file) fopen(file, "w");

/**
 * Prints in stderr
 * @param format string to print
 * @param __VA_ARGS__ args to be formatted
 */
#define TO_STDERR(format, ...) \
            fprintf(stderr, ">>> " format ".\n", ##__VA_ARGS__)

/**
 * Prints in stdout
 * @param format string to print
 * @param __VA_ARGS__ args to be formatted
 */
#define TO_STDOUT(format, ...) \
            fprintf(stdout, ">>> " format ".\n", ##__VA_ARGS__)

/**
 * Prints in given file
 * @param file where to print
 * @param format string to print
 * @param __VA_ARGS__ args to be formatted
 */
#define TO_FILE(file, format, ...) \
            fprintf(file, format "\n", ##__VA_ARGS__)

/**
 * Buff size
 */
#define BUFF 128

/**
 * Max identifiers length
 */
#define MAX_LEN 100

/**
 * Unexpected error macro
 */
#define UNSP_ERR INT_MIN

/**
 * None value
 */
#define NONE INT_MAX

/**
 * Key max size
 */
#define _KEY_MAX_SIZE_ MAX_LEN

/**
 * Copies from tf to te a maximum of BUFF chars
 */
#define COPY(te, tf) \
            strncpy(te, tf, BUFF)

/**
 * Updates errbuff info
 * @param file where failure occured
 * @param str string to print
 */
#define COPYERR(file, str, ...) \
            snprintf(errbuff, BUFF, "*** at %s: [at line: %d; col: %d]: " str, file, line, col, ##__VA_ARGS__);

/**
 * Vector's maximum length
 */
#define _VECTOR_MAX_LEN_ 64

/**
 * Vector's minimum length
 */
#define _VECTOR_MIN_LEN_ 1

/**
 * Category with the element's class {VAR, PARAM, FUNCT}
 */
enum _ElementCategory
{
  VAR,
  PARAM,
  FUNCT
};

/**
 * Type of the elements {BOOLEAN, INT}
 */
enum _DataType
{
  BOOLEAN,
  INT
};

/**
 * Elements identifier {SCALAR, VECTOR}
 */
enum _IdentifierCategory
{
  SCALAR,
  VECTOR
};

/**
 * Scope of the elements {GLOBAL, LOCAL}
 */
enum _Scope
{
  GLOBAL,
  LOCAL
};


/**
 * Type definition for ElementCategory
 */
typedef enum _ElementCategory ElementCategory;

/**
 * Type definition for DataType
 */
typedef enum _DataType DataType;

/**
 * Type definition for IdentifierCategory
 */
typedef enum _IdentifierCategory IdentifierCategory;

/**
 * Type definition for Scope
 */
typedef enum _Scope Scope;

/**
 * Type definition for Symbol
 */
typedef struct _Symbol Symbol;

/**
 * Type definition for attributes info
 */
typedef struct _attrs_type attrs_type;

/**
 * Type definition for String
 */
typedef char* String;

/**
 * Common error buffer
 */
extern char errbuff[BUFF];

/**
 * To manage failures come from
 */
extern bool morfofailure;

/**
 * To control current parse line
 */
extern int line;

/**
 * To control current parse column
 */
extern int col;

/**
 * Structure with semantic info
 */
struct _attrs_type
{
  char lexeme[MAX_LEN + 1];
  int int_value;
  DataType type;
};

#endif