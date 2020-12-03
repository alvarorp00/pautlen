#ifndef ALFA_H
#define ALFA_H

#include <stdbool.h>

/* Methods that converts literal to string */
#define STR(x) #x

/* Opens file in read mode */
#define READ(file) fopen(file, "r");

/* Opens file in write mode, removes previous data */
#define WRITE(file) fopen(file, "w");

/* Common buffer size */
#define BUFF 128

/* Copies data in tf to te, respectful with buffer size */
#define COPY(te, tf) \
            strncpy(te, tf, BUFF)

/* Updates errbuff in case of an error */
#define COPYERR(file, str, ...) \
            snprintf(errbuff, BUFF, "*** at %s: [at line: %d; col: %d]: " str, file, line, col, ##__VA_ARGS__);

/* Common error buffer */
extern char errbuff[BUFF];

/* Common morfologic failure flag */
extern bool morfofailure;

/* Commmon line counter */
extern int line;

/* Common column counter */
extern int col;

#endif