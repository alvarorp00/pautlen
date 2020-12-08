#ifndef SET_H
#define SET_H

#include "prototypes.h"


#define SET_SIZE( st ) ( st )->size
#define SET_IDX( st ) ( st )->idx
#define SET_AT( st, idx ) ( st )->set[idx]
#define SET__( s ) ( s )->set

typedef struct dyn_set {
  int idx;
  int size;
  cmp_proto cmp_fn;
  cpy_proto cpy_fn;
  free_proto free_fn;
  print_proto print_fn;
  void **set;
} dyn_set_t;

dyn_set_t* set_init( cpy_proto cpy_fn, cmp_proto cmp_fn, free_proto free_fn, print_proto print_fn );
void set_check_size( dyn_set_t *set );
dyn_set_t* set_append( dyn_set_t *set, void *ptr );
void set_free( dyn_set_t *set );
void set_print( FILE *fp, dyn_set_t *set );
dyn_set_t* set_append_sorted( dyn_set_t *set, void *ptr );

#endif