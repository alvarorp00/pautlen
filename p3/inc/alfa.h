#ifndef ALFA_H
#define ALFA_H

#include <stdbool.h>

#define STR(x) #x

#define READ(file) fopen(file, "r");
#define WRITE(file) fopen(file, "w");

#define BUFF 128

#define COPY(te, tf) \
            strncpy(te, tf, BUFF)

#define COPYERR(file, str, ...) \
            snprintf(errbuff, BUFF, "*** at %s: [at line: %d; col: %d]: " str, file, line, col, ##__VA_ARGS__);

extern char errbuff[BUFF];
extern bool morfofailure;

extern int line;
extern int col;

#endif