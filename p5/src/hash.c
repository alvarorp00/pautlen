/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"
#include "symbol.h"

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
static Node* init_node(Node *node, void* info);

/**
 * Deleted a node and it's info
 * @param node to clean
 * @param clean info's clean function
 */
static void delete_node(Node *node, Clean clean);

static void clean_nodes(Node **nodes,Clean clean, size_t max_size);

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

  if(!hash->nodes)
  {
    hash_clean(hash);
    return false;
  }

  return true;
}

void hash_clean(Hash *hash)
{
  size_t i;
  
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
  // printf("Reponse index: %ld\n", response.index);
  // printf("Response.present: %s\n", response.present ? "True": "False");
  if(response.present == true)
    return false;

  hash->nodes[response.index] = init_node(hash->nodes[response.index], info);
  hash->curr_size += 1;

  printf("\tInserted in %ld\n", response.index);

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

  printf("\tTrying to acces %ld\n",response.index);
  printf("\t\tPresent: %s n", response.present ? "True" : "False");
  
  if(response.present == false)
    return NULL;

  return hash->nodes[response.index]->info;
}

bool hash_deleteinfo(Hash *hash, void* info)
{
  ProbingResponse response;
 
  if(!hash || !info)
    return false;

  if(hash->curr_size == 0)
    return false;
  
  response = linearProbing(
    hash->nodes,
    info,
    hash->hashcode,
    hash->equals,
    hash->max_size
  );
  if(response.present == false)
    return false;
  
  delete_node(hash->nodes[response.index], hash->clean);

  hash->curr_size -= 1;
  refactor_ifNeeded(hash);

  return true;
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
  size_t i;
  
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
          printf("\n\n\tFound ! at %ld\n\n", val);
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
  uint_fast16_t new_size;
  uint_fast64_t i;
  ProbingResponse r_response;
  Node **new_nodes;
  
  if(!hash)
    return;
  
  hash->factor = (float)(hash->curr_size)/(float)(hash->max_size);
  printf("Current factoor: %f\n", hash->factor);

  if (hash->factor == 0)
  {
    hash->nodes = (Node**)calloc(_DEF_HASHLEN_, sizeof(Node*));
    hash->max_size = _DEF_HASHLEN_;
    return;
  }

  if(hash->factor > _LOW_CRITICAL_FACTOR_ && hash->factor < _HIGH_CRITICAL_FACTOR_)
    return;

  if(hash->factor > _HIGH_CRITICAL_FACTOR_)
    new_size = hash->max_size << 1;
  else if(hash->factor < _LOW_CRITICAL_FACTOR_)
    new_size = hash->max_size >> 1;

  printf("New size: %ld\n", new_size);

  new_nodes = (Node**)calloc(new_size, sizeof(Node*));
  
  for(i = 0; i < hash->max_size; i++)
  {
    if(node_isEmpty(hash->nodes[i]))
      continue;
    
    r_response = linearProbing(
      new_nodes,
      hash->nodes[i]->info,
      hash->hashcode,
      hash->equals,
      new_size
    );

    if(r_response.present)
      continue;

    new_nodes[r_response.index] = hash->nodes[i];
  }

  free(hash->nodes);
  hash->nodes = new_nodes;
  hash->max_size = new_size;
  
  hash->factor = (float)hash->curr_size/(float)hash->max_size;
  printf("Realloc'd -> new factor: %f\n", hash->factor);
}

static Node* init_node(Node *node, void* info)
{
  node = (Node*)calloc(1,sizeof(Node));
  node->info = info; 
  return node;
}

static void delete_node(Node *node, Clean clean)
{
  if(!node)
    return;
  if(node->info)
    clean(node->info);
  node->info = NULL;
  free(node);
  node = NULL;
}

static void clean_nodes(Node **nodes, Clean clean, size_t max_size)
{
  size_t i;
  
  for(i = 0; i < max_size; i++)
  {
    if(nodes[i] != NULL)
      delete_node(nodes[i], clean);
  }
}

static bool node_isEmpty(Node *node)
{
  if(node == NULL)
    return true;
  
  return node->info == NULL;
}

void print_hash(Hash *hash)
{
  size_t i;
  
  if(!hash)
    return;
  
  printf("\nMax size: %ld\n", hash->max_size);
  printf("Current size: %ld\n", hash->curr_size);
  printf("Load factor: %f\n",hash->factor);
  for(i = 0; i < hash->max_size; i++)
  {
    if(node_isEmpty(hash->nodes[i]))
      continue;
    printf("Value at [ %ld ] --> %s\n", i, symbol_get_key(hash->nodes[i]->info));
  }
}
