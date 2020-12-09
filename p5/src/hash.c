/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"

typedef struct _ProbingResponse ProbingResponse;
typedef struct _Node Node;

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
static bool init_nodes(Hash *hash);

/**
 * Checks if node is empty
 * @param node to check
 * @return if it's empty
 */
static bool node_isEmpty(Node *node);

/**
 * Initializes a new node
 * @param node to initialize
 * @param info to store in node
 * @return same node
 */
static Node* init_node(void* info);

static void clean_nodes(Node **nodes,Clean clean, uint_fast64_t max_size);

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
static void refactor_ifNeeded(Hash *hash);

/* ----------------------- */

Hash *hash_init(Hashcode hashcode, Equals equals, Clean clean)
{
  Hash *hash;

  if(!hashcode || !equals || !clean)
    return NULL;

  hash = (Hash*)calloc(1,sizeof(Hash));
  if(!hash)
    return NULL;
  
  hash->hashcode = hashcode;
  hash->equals = equals;
  hash->clean = clean;

  if(!init_nodes(hash))
  {
    hash_clean(hash);
    return NULL;
  }

  return hash;
}

static bool init_nodes(Hash *hash)
{
  if(!hash)
    return false;

  hash->nodes = (Node**)calloc(_DEF_HASHLEN_, sizeof(Node*));
  hash->max_size = _DEF_HASHLEN_;
  hash->curr_size = 0;
  hash->factor = 0;

  memset(hash->nodes, 0, sizeof(Node*)*_DEF_HASHLEN_);

  if(!hash->nodes)
  {
    hash_clean(hash);
    return false;
  }

  return true;
}

void hash_clean(Hash *hash)
{  
  if(!hash)
    return;

  clean_nodes(hash->nodes, hash->clean, hash->max_size);

  free(hash->nodes);

  free(hash);
  
}

bool hash_encode(Hash *hash, void* info)
{
  ProbingResponse response;
  
  if(!info)
    return false;

  response = linearProbing(
    hash->nodes,
    info,
    hash->hashcode,
    hash->equals,
    hash->max_size
  );

  if(response.present == true)
    return false;

  hash->nodes[response.index] = init_node(info);
  hash->curr_size += 1;

  refactor_ifNeeded(hash);
  
  return true;
}

void* hash_decode(Hash *hash, void* info)
{
  ProbingResponse response;

  response = linearProbing(
    hash->nodes,
    info,
    hash->hashcode,
    hash->equals,
    hash->max_size
  );
  
  if(response.present == false)
    return NULL;

  return hash->nodes[response.index]->info;
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
  
  hashed = hashcode(info) % max_size;

  for (i = 0; i < max_size; i++)
  {
    val = (hashed + i)%max_size;

    if(!node_isEmpty(nodes[val]))
    {
      if(equals(nodes[val]->info, info))
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

bool hash_contains(Hash *hash, void* info)
{
  ProbingResponse response;

  if(!hash || !info)
    return false;

  if(hash->factor == 0)
    return false;

  response = linearProbing(
    hash->nodes,
    info,
    hash->hashcode,
    hash->equals,
    hash->max_size
  );

  return response.present;
}

static void refactor_ifNeeded(Hash *hash)
{
  Node **__nodes;
  ProbingResponse r_response;
  uint_fast64_t __size;
  uint_fast64_t i;
  
  if(!hash)
    return;
  
  hash->factor = (float)(hash->curr_size)/(float)(hash->max_size);

  if(hash->factor < _HIGH_CRITICAL_FACTOR_)
    return;

  __size = hash->max_size << 1;
  __nodes = (Node**)calloc(__size, sizeof(Node*));
  memset(__nodes, 0, sizeof(Node*)*_DEF_HASHLEN_);
  
  for(i = 0; i < hash->max_size; i++)
  {
    if(node_isEmpty(hash->nodes[i]))
    {
      free(hash->nodes[i]);
      continue;
    }
    
    r_response = linearProbing(
      __nodes,
      hash->nodes[i]->info,
      hash->hashcode,
      hash->equals,
      __size
    );

    __nodes[r_response.index] = hash->nodes[i];
  }
  
  free(hash->nodes);
  hash->nodes = __nodes;
  hash->max_size = __size;
  hash->factor = (float)hash->curr_size/(float)hash->max_size;

}

static Node* init_node(void* info)
{
  Node *node;
  
  if(!info)
    return NULL;
  
  node = (Node*)calloc(1,sizeof(Node));
  node->info = info; 

  return node;
}

static void clean_nodes(Node **nodes, Clean clean, uint_fast64_t max_size)
{
  uint_fast64_t i;
  
  for(i = 0; i < max_size; i++)
  {
    if(node_isEmpty(nodes[i]))
      continue;
    if(nodes[i]->info != NULL)
    {
      clean(nodes[i]->info);
    }
    free(nodes[i]);
    nodes[i] = NULL;
  }
}

static bool node_isEmpty(Node *node)
{ 
  return node == NULL;
}

/* ------------------------------- */

hash_iterator *hash_iterate(Hash *hash)
{
  uint_fast64_t i;
  hash_iterator *iterator;
  iterator_node *__inode, *__prev_inode;
  
  if(!hash)
    return NULL;

  iterator = (hash_iterator*)calloc(1, sizeof(hash_iterator));
  if(!iterator)
    return NULL;

  __inode = (iterator_node*)calloc(1, sizeof(hash_iterator));
  if(!__inode)
    {
      hash_iterate_clean(iterator);
      return NULL;
    }

  // Find first
  for(i = 0; i < hash->max_size; i++)
  {
    if(node_isEmpty(hash->nodes[i]))
      continue;
    break; // We've found the first node
  }

  __inode->info = (void*)hash->nodes[i]->info;
  __inode->__next = NULL;

  iterator->first = __inode;

  for(i++; i < hash->max_size; i++)
  {
    if(node_isEmpty(hash->nodes[i]))
      continue;
    __prev_inode = __inode;
    __inode = (iterator_node*)calloc(1, sizeof(hash_iterator));
    if(!__inode)
      {
        hash_iterate_clean(iterator);
        return NULL;
      }
    __prev_inode->__next = __inode;
    __inode->info = (void*)hash->nodes[i]->info;
    __inode->__next = NULL;
  }

  return iterator;
}

iterator_node *first(hash_iterator *iterator)
{
  if(!iterator)
    return NULL;
  return iterator->first;
}

iterator_node *next(iterator_node *_inode)
{
  if(!_inode)
    return NULL;
  return _inode->__next;
}

void hash_iterate_clean(hash_iterator *iterator)
{
  iterator_node *__inode, *__next_inode;
  
  if(!iterator)
    return;
  
  __inode = first(iterator);
  while(next(__inode) != NULL)
  {
    __next_inode = next(__inode);
    free(__inode);
    __inode = __next_inode;
  }
  free(__inode);

  free(iterator);
}
