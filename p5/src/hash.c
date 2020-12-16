/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"

#define H__MAX( h ) ( h )->max_size
#define H__SIZE( h ) ( h )->curr_size
#define H__FACTOR( h ) ( h )->factor 
#define H__NODES( h ) ( h )->nodes
#define H__NODE_AT( h, i ) ( h )->nodes[i]
#define H__INFO( h, i ) ( h )->nodes[i]->info

#define NS__INFO_AT( n, i ) ( n[i] )->info
#define N__INFO( n ) ( n )->info

typedef struct _ProbingResponse ProbingResponse;
typedef struct _Node Node;

struct _iterator_node
{
  void *info;
  iterator_node *__next;
};

struct _hash_iterator
{
  uint_fast64_t size;
  iterator_node *first;
};

struct _ProbingResponse
{
  bool present;
  uint_fast64_t index;
};

/**
 * Node in hash
 */
struct _Node {
  void *info; /* Node info */
};

/**
 * Main hash structure
 */
struct _Hash {
  uint_fast64_t max_size;
  uint_fast64_t curr_size;
  float factor;
  Node **nodes; /* Hash nodes which store info */
  Hashcode hashcode;
  Equals equals;
  Clean clean;
};

/* ----------------------- */

/* hash FUNCTIONS DECLARATIONS */

/**
 * Starts hash nodes array
 * @param hash where nodes will be stored
 * @return if was posible
 */
static bool init_nodes( Hash *hash );

/**
 * Checks if node is empty
 * @param node to check
 * @return if it's empty
 */
static bool node_isEmpty( Node *node );

/**
 * Initializes a new node
 * @param node to initialize
 * @param info to store in node
 * @return same node
 */
static Node* init_node( void* info );

static void clean_nodes( Node **nodes,Clean clean, uint_fast64_t max_size );

/**
 * Linear probing for hash structure
 * @param hash to check
 * @param info info to check
 * @return ProbingResponse object
 */
static ProbingResponse linearProbing( 
  Node **nodes,
  void *info,
  Hashcode hashcode,
  Equals equals,
  uint_fast64_t max_size
 );

/**
 * Refactors hash size if it's needed
 * @param hash to resize
 */
static void refactor_ifNeeded( Hash *hash );

/* ----------------------- */

Hash *hash_init( Hashcode hashcode, Equals equals, Clean clean )
{
  Hash *hash;

  if( !hashcode || !equals || !clean )
    return NULL;

  hash = ( Hash* )calloc( 1,sizeof( Hash ) );
  if( !hash )
    return NULL;
  
  hash->hashcode = hashcode;
  hash->equals = equals;
  hash->clean = clean;

  if( !init_nodes( hash ) )
  {
    hash_clean( hash );
    return NULL;
  }

  return hash;
}

static bool init_nodes( Hash *hash )
{
  if( !hash )
    return false;

  H__NODES( hash ) = (Node** )calloc(_DEF_HASHLEN_, sizeof(Node* ) );
  H__MAX( hash ) = _DEF_HASHLEN_;
  H__SIZE( hash ) = 0;
  H__FACTOR( hash ) = 0;

  memset(H__NODES( hash ), 0, sizeof(Node* )*_DEF_HASHLEN_ );

  if(!H__NODES( hash ) )
  {
    hash_clean(hash );
    return false;
  }

  return true;
}

void hash_clean(Hash *hash )
{  
  if(!hash )
    return;

  clean_nodes(H__NODES( hash ), hash->clean, H__MAX( hash ) );

  free(H__NODES( hash ) );

  free(hash );
  
}

bool hash_encode(Hash *hash, void* info )
{
  ProbingResponse response;
  
  if(!info )
    return false;

  response = linearProbing(
    H__NODES( hash ),
    info,
    hash->hashcode,
    hash->equals,
    H__MAX( hash )
 );

  if( response.present == true )
    return false;

  H__NODE_AT( hash, response.index ) = init_node(info );
  H__SIZE( hash ) += 1;

  refactor_ifNeeded( hash );
  
  return true;
}

void* hash_decode( Hash *hash, void* info )
{
  ProbingResponse response;

  response = linearProbing( 
    H__NODES( hash ),
    info,
    hash->hashcode,
    hash->equals,
    H__MAX( hash )
 );

  
  if( response.present == false )
    return NULL;

  return H__INFO( hash, response.index );
}

static ProbingResponse linearProbing( 
  Node **nodes,
  void* info,
  Hashcode hashcode,
  Equals equals,
  uint_fast64_t max_size
 )
{
  ProbingResponse response;
  uint_fast64_t hashed, val;
  uint_fast64_t i;
  
  hashed = hashcode( info ) % max_size;

  for ( i = 0; i < max_size; i++ )
  {
    val = ( hashed + i )%max_size;


    if( !node_isEmpty( nodes[val] ) )
    {
      if( equals( NS__INFO_AT( nodes, val ), info ) )
      {
        response.index = val;
        response.present = true;
        return response;
      }
    }
    else
    {
      response.index = val;
      response.present = false;
      return response;
    }
  }

  response.present = false;
  response.index = max_size;
  
  return response;
}

bool hash_contains( Hash *hash, void* info )
{
  ProbingResponse response;

  if( !hash || !info )
    return false;

  if( H__FACTOR( hash ) == 0 )
    return false;

  response = linearProbing( 
    H__NODES( hash ),
    info,
    hash->hashcode,
    hash->equals,
    H__MAX( hash )
 );

  return response.present;
}

static void refactor_ifNeeded( Hash *hash )
{
  Node **__nodes;
  ProbingResponse r_response;
  uint_fast64_t __size;
  uint_fast64_t i;
  
  if( !hash )
    return;
  
  H__FACTOR( hash ) = ( float )( H__SIZE( hash ) )/( float )( H__MAX( hash ) );

  if( H__FACTOR( hash ) < _HIGH_CRITICAL_FACTOR_ )
    return;

  __size = ( H__MAX( hash ) ) << 1;
  __nodes = ( Node** )calloc( __size, sizeof( Node* ) );
  memset( __nodes, 0, sizeof( Node* )*_DEF_HASHLEN_ );

  
  for( i = 0; i < H__MAX( hash ); i++ )
  {
    if( node_isEmpty( H__NODE_AT( hash, i ) ) )
    {
      free( H__NODE_AT( hash, i ) );
      continue;
    }
    
    r_response = linearProbing( 
      __nodes,
      H__INFO( hash, i ),
      hash->hashcode,
      hash->equals,
      __size
    );

    __nodes[r_response.index] = H__NODE_AT( hash, i );
  }
  
  free( H__NODES( hash ) );
  H__NODES( hash ) = __nodes;
  H__MAX( hash ) = __size;
  H__FACTOR( hash ) = ( float )H__SIZE( hash )/( float )H__MAX( hash );

}

static Node* init_node( void* info )
{
  Node *node;
  
  if( !info )
    return NULL;
  
  node = ( Node* )calloc( 1,sizeof( Node ) );
  N__INFO( node ) = info; 

  return node;
}

static void clean_nodes( Node **nodes, Clean clean, uint_fast64_t max_size )
{
  uint_fast64_t i;
  
  for( i = 0; i < max_size; i++ )
  {
    if( node_isEmpty( nodes[i] ) )
      continue;
    if( NS__INFO_AT( nodes, i ) != NULL )
    {
      clean( NS__INFO_AT( nodes, i ) );
    }
    free( nodes[i] );
    nodes[i] = NULL;
  }
}

static bool node_isEmpty( Node *node )
{ 
  return node == NULL;
}

/* ------------------------------- */

hash_iterator *hash_iterate( Hash *hash )
{
  uint_fast64_t i;
  hash_iterator *iterator;
  iterator_node *__inode, *__prev_inode;
  
  if( !hash )
    return NULL;

  iterator = ( hash_iterator* )calloc( 1, sizeof( hash_iterator ) );
  if( !iterator )
    return NULL;

  __inode = ( iterator_node* )calloc( 1, sizeof( hash_iterator ) );
  if( !__inode )
    {
      hash_iterate_clean( iterator );
      return NULL;
    }

  // Find first
  for( i = 0; i < H__MAX( hash ); i++ )
  {
    if( node_isEmpty( H__NODE_AT( hash, i ) ) )
      continue;
    break; // We've found the first node
  }

  __inode->info = ( void* )H__INFO( hash, i );
  __inode->__next = NULL;

  iterator->first = __inode;

  for( i++; i < H__MAX( hash ); i++ )
  {
    if( node_isEmpty( H__NODE_AT( hash, i ) ) )
      continue;
    __prev_inode = __inode;
    __inode = ( iterator_node* )calloc( 1, sizeof( hash_iterator ) );
    if( !__inode )
      {
        hash_iterate_clean( iterator );
        return NULL;
      }
    __prev_inode->__next = __inode;
    __inode->info = ( void* )H__INFO( hash, i );
    __inode->__next = NULL;
  }

  return iterator;
}

iterator_node *first( hash_iterator *iterator )
{
  return iterator == NULL ? NULL : iterator->first;
}

iterator_node *next( iterator_node *_inode )
{
  return _inode == NULL ? NULL : _inode->__next;
}

void *iter_nodeInfo( iterator_node *_inode )
{
  return _inode == NULL ? NULL : _inode->info;
}

bool hasNext( iterator_node *_inode )
{
  return _inode == NULL ? false : _inode->__next != NULL;
}

void hash_iterate_clean( hash_iterator *iterator )
{
  iterator_node *__inode, *__next_inode;
  
  if( !iterator )
    return;
  
  __inode = first( iterator );
  while( next( __inode ) != NULL )
  {
    __next_inode = next( __inode );
    free( __inode );
    __inode = __next_inode;
  }
  free( __inode );

  free( iterator );
}
