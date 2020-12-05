/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"
#include "symbol.h"

typedef struct _Node Node;

struct _Node {
  void *value;
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
 * @param value to store in node
 * @return same node
 */
static Node* init_node(Node *node, void* value);

/**
 * Deleted a node and it's value
 * @param node to clean
 * @param clean value's clean function
 */
static void delete_node(Node *node, Clean clean);

/**
 * Linear probing for hash structure
 * @param hash to check
 * @param value value to check
 * @return index in hash
 */
static uint_fast64_t linearProbing(Hash *hash, void *value);

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

  if(!hash->nodes)
  {
    hash_clean(hash);
    return false;
  }

  return true;
}

void hash_clean(Hash *hash)
{
  uint_fast64_t i;
  
  if(!hash)
    return;

  for(i = 0; i < hash->max_size; i++)
  {
    if(hash->nodes[i] != NULL)
      delete_node(hash->nodes[i], hash->clean);
  }

  free(hash->nodes);

  free(hash);
  
}

bool hash_encode(Hash *hash, void* value)
{
  uint_fast64_t hashed;
  
  if(!value)
    return false;
  if(hash_contains(hash, value))
    return false;

  hashed = linearProbing(hash, value);

  hash->nodes[hashed] = init_node(hash->nodes[hashed], value);
  hash->curr_size += 1;

  refactor_ifNeeded(hash);
  
  return true;
}

void* hash_decode(Hash *hash, void* value)
{
  uint_fast64_t hashed;

  hashed = linearProbing(hash, value);
  
  if(!hash_contains(hash, value))
    return NULL;

  return hash->nodes[hashed]->value;
}

bool hash_deleteValue(Hash *hash, void* value)
{
  uint_fast64_t hashed;
 
  if(!hash || !value)
    return false;

  if(!hash_contains(hash, value))
    return false;
  
  hashed = linearProbing(hash, value);
  delete_node(hash->nodes[hashed], hash->clean);

  hash->curr_size -= 1;
  refactor_ifNeeded(hash);

  return true;
}

static uint_fast64_t linearProbing(Hash *hash, void* value)
{
  uint_fast64_t hashed, val;
  uint_fast64_t i;
  
  hashed = hash->hashcode(value) % hash->max_size;

  for (i = 0; i < hash->max_size; i++)
  {
    val = (hashed + i)%hash->max_size;

    if(!node_isEmpty(hash->nodes[val]))
    {
      if(hash->equals(hash->nodes[val]->value, value))
        {
          return val;
        }
    }
    else
    {
      return val;
    }
  }
  
  return i;
}

bool hash_contains(Hash *hash, void* value)
{
  uint_fast64_t hashed;

  if(!hash || !value)
    return false;

  hashed = linearProbing(hash, value);

  if(hashed == hash->max_size)
    return false;

  if(node_isEmpty(hash->nodes[hashed]))
    return false;
  
  return hash->equals(hash->nodes[hashed]->value, value);
}

static void refactor_ifNeeded(Hash *hash)
{
  if(!hash)
    return;
  
  hash->factor = (float)(hash->curr_size)/(float)(hash->max_size);

  if(hash->factor > _LOW_CRITICAL_FACTOR_ && hash->factor < _HIGH_CRITICAL_FACTOR_)
    return;

  if(hash->factor > _HIGH_CRITICAL_FACTOR_)
    hash->max_size <<= 1;
  else if(hash->factor < _LOW_CRITICAL_FACTOR_)
    hash->max_size >>= 1;
  hash->nodes = (Node**)realloc(hash->nodes, sizeof(Node*)*hash->max_size);
}

static Node* init_node(Node *node, void* value)
{
  node = (Node*)calloc(1,sizeof(Node));
  node->value = value;
  return node;
}

static void delete_node(Node *node, Clean clean)
{
  if(!node)
    return;
  if(node->value)
    clean(node->value);
  node->value = NULL;
  free(node);
  node = NULL;
}

static bool node_isEmpty(Node *node)
{
  if(node == NULL)
    return true;
  
  return node->value == NULL;
}
