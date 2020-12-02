/**
 * 
 *  HEADER
 * 
 * 
 */

#include <stdint.h>
#include "hash.h"
#include "symbol.h"

typedef struct _Node Node;

struct _Node {
  bool empty;
  void *value;
};

/**
 * Main hash structure
 */
struct _Hash {
  uint_fast32_t max_size;
  uint_fast32_t curr_size;
  float factor;
  Node **nodes; /* Hash nodes which store info */
  Hashcode hashcode;
  Equals equals;
  Clean clean;
};

/* ----------------------- */

/* hash FUNCTIONS DECLARATIONS */

static bool init_nodes(Hash *hash);
static bool node_isEmpty(Node *node);

static size_t linearProbing(Hash *hash, void *value);


/* ----------------------- */

Hash *hash_init(Hashcode hashcode, Equals equals, Clean clean)
{
  Hash *hash;

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
  size_t i;
  
  if(!hash)
    return false;

  hash->nodes = (Node**)calloc(_DEF_HASHLEN_, sizeof(Node*));
  hash->max_size = _DEF_HASHLEN_;
  hash->curr_size = 0;

  if(!hash->nodes)
  {
    hash_clean(hash);
    return false;
  }

  for(i = 0; i < hash->max_size; i++)
  {
    hash->nodes[i] = (Node*)calloc(1, sizeof(Node));
    if(!hash->nodes[i])
    {
      hash_clean(hash);
      return false;
    }
  }

  return true;
}

void hash_clean(Hash *hash)
{
  size_t i;
  
  if(!hash)
    return;

  for(i = 0; i < hash->max_size; i++)
  {
    if(hash->nodes[i]->value != NULL)
    {
      hash->clean(hash->nodes[i]->value);
    }
  }

  free(hash);
  
}

bool hash_encode(Hash *hash, void* value)
{
  size_t hashed;
  
  if(!value)
    return false;
  if(hash_contains(hash, value))
    return false;

  hashed = linearProbing(hash, value);

  hash->nodes[hashed]->value = value;

  return true;
}

void* hash_decode(Hash *hash, void* value)
{
  if(!hash_contains(hash, value))
    return NULL;

  return hash->nodes[linearProbing(hash, value)]->value;
}

void hash_deleteValue(Hash *hash, void* value)
{
  size_t hashed;
 
  if(!hash || !value)
    return;

  if(!hash_contains(hash, value))
    return;
  
  hashed = linearProbing(hash, value);
  hash->clean(hash->nodes[hashed]->value);
}

static size_t linearProbing(Hash *hash, void* value)
{
  size_t hashed, val;
  size_t i;
  
  hashed = hash->hashcode(value) % hash->max_size;

  for (i = 0; i < hash->max_size; i++)
  {
    val = (hashed + i)%hash->max_size;

    if(!node_isEmpty(hash->nodes[val]))
    {
      if(hash->equals(hash->nodes[val], value))
        {
          return val;
        }
    }
    return val;
  }
  
  return i;
}

bool hash_contains(Hash *hash, void* value)
{
  size_t hashed;

  if(!hash || !value)
    return false;

  hashed = linearProbing(hash, value);

  if(hashed == hash->max_size)
    return false;

  if(node_isEmpty(hash->nodes[hashed]))
    return false;
  
  return hash->equals(hash->nodes[hashed]->value, value);
}

bool node_isEmpty(Node *node)
{
  if(!node)
    return false;
  
  return node->value == NULL;
}
