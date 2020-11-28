#ifndef ALFA_H
#define ALFA_H

#include <stdbool.h>
#include "tokens.h"

#define STR(x) #x

#define READ(file) fopen(file, "r");
#define WRITE(file) fopen(file, "w");

#define BUFF 128

#define COPY(te, tf) \
            strncpy(te, tf, BUFF)

extern char errbuff[BUFF];

extern bool morfofailure;

#endif