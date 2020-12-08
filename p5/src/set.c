#include "set.h"
#include "prototypes.h"
#include <stdlib.h>
#include <stdbool.h>

dyn_set_t* set_init(
  cpy_proto cpy_fn,
  cmp_proto cmp_fn,
  free_proto free_fn,
  print_proto print_fn
) {

  dyn_set_t *set = (dyn_set_t*)malloc( sizeof( dyn_set_t ) );

  if ( !set ) {
    return NULL;
  }

  set->cpy_fn = cpy_fn;
  set->cmp_fn = cmp_fn;
  set->free_fn = free_fn;
  set->print_fn = print_fn;

  set->size = 1;
  set->idx = -1; // points to the last id
  set->set = (void**) malloc( sizeof(void*) );

  if ( !set->set ) {
    free( set );
    return NULL;
  }
  
  return set;
}

void set_check_size( dyn_set_t *set ) {
    // alloc more memory
  if ( SET_IDX(set)+1 >= SET_SIZE( set )  ) {

    int newSize = SET_SIZE(set) << 1;
    SET__( set ) = (void**) realloc( SET__( set ), sizeof(void*)*newSize );
    SET_SIZE( set ) = newSize;
  }
}


dyn_set_t* set_append( dyn_set_t *set, void *ptr ) {

  set_check_size( set );
  
  bool found = false;
  int i = SET_IDX( set );

  while (i >= 0) {
    if ( set->cmp_fn( ptr, SET_AT( set, i ) ) == 0 ) {
      found = true;
      break;
    }
    i--;
  }

  if ( !found ) {
    if ( set->cpy_fn ) {
      ptr = set->cpy_fn( ptr );
    }
    SET_AT( set, ++SET_IDX( set ) ) = ptr;
  }

  return set;
}

void set_free( dyn_set_t *set ) {

  if ( set->free_fn ) {
    for ( int i=0; i<=SET_IDX( set ); i++ ) {
      set->free_fn( SET_AT( set, i ) );
    }
  }

  free( SET__( set ) );
  free( set );
}

void set_print( FILE *fp, dyn_set_t *set ) {

  fprintf( fp, "{" );
  if ( set->print_fn ) {
    for ( int i=0; i<=SET_IDX( set ); i++ ) {
      set->print_fn( fp, SET_AT( set, i ) );
      if ( i < SET_IDX( set ) ) {
        fprintf( fp, "," );
      }
    }
  }
  fprintf( fp, "}" );

}

dyn_set_t* set_append_sorted( dyn_set_t *set, void *ptr ) {

  set_check_size( set );

  if ( set->cpy_fn ) {
    ptr = set->cpy_fn( ptr );
  }

  int from, m, to;
  bool found = false;
  
  from = 0;
  to = SET_IDX( set );

  while ( from <= to ) {
    
    m = from + (to-from)/2;
    int cmp = set->cmp_fn( ptr, SET_AT( set, m ) ); 

    if ( cmp == 0 ) { // found
      found = true;
      break;
    }

    if ( cmp > 0 ) {
      from=m+1;
    } else {
      to=m-1;
    }

  }

  if ( !found ) {

    SET_AT( set, ++SET_IDX( set ) ) = ptr;
    int i = SET_IDX( set );

    while ( i && set->cmp_fn( ptr, SET_AT( set, i-1 ) ) < 0 ) {
      swap( &SET_AT( set, i ), &SET_AT( set, i-1 ) );
      i--;
    }

  }

  return set;
}