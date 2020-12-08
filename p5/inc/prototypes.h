#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>

typedef int (*cmp_proto) ( void*, void* );
typedef void* (*cpy_proto) ( void* );
typedef void (*free_proto) ( void* );
typedef void (*print_proto) ( FILE*, void* );

#endif