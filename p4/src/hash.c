/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"

typedef struct _Node Node;
typedef struct _Variable Variable;
typedef struct _Parametre Parametre;
typedef struct _Function Function;

typedef union _Element Element;

/**
 * Structure with alfa's variables info
 */
struct _Variable
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  __u_int size; /* Size of the variable in case it's a VECTOR */
  Scope scope; /* Scope {LOCAL, GLOBAL} */
  __u_short pos; /* Position in function in case it's in LOCAL Scope */
};

/**
 * Structure with alfa's parametres info
 */
struct _Parametre
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  __u_int size; /* Size of the parametre in case it's a VECTOR */
  __u_short pos;
};

/**
 * Structure with alfa's functions info
 */
struct _Function
{
  __u_short params; /* Number of function parametres */
  __u_short localvars; /* Number of function local variables */
};

/**
 * Union with element stored
 */
union _Element
{
  Variable var; /* Element is a variable */
  Parametre param; /* Element is a parametre */
  Function func; /* Element is a function */
};

/**
 * Helper structure to store multiple info values
 */
struct _Node {
  bool empty; /* To control if this node is empty or not */
  char key[_KEY_MAX_SIZE_]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in union {Function, Parametre, Variable} */
  Element element; /* Element */
};

/**
 * Main hash structure
 */
struct _Hash {
  Node *values[_DEF_HASHLEN_]; /* Hash nodes which store info */
};

/* ----------------------- */

/* SELF FUNCTIONS DECLARATIONS */

static bool init_nodes(Hash *hash);

static size_t hashcode(String identifier);
static bool hash_contains(Hash *self, String identifier);

/* ----------------------- */

Hash *hash_init()
{
  Hash *hash;

  size_t i;

  hash = (Hash*)calloc(1,sizeof(Hash));
  if(!hash)
    return NULL;

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
  
  for(i = 0; i < _DEF_HASHLEN_; i++)
  {
    hash->values[i] = (Node*)calloc(1,sizeof(Node));
    if(!hash->values[i])
    {
      return false;
    }
    hash->values[i]->empty = true;
    hash->values[i]->key = NULL;
  }
}

void hash_clean(Hash *self)
{
  size_t i;

  Function f;
  
  if(!self)
    return;

  for (i = 0; i < _DEF_HASHLEN_; i++)
  {
    if(self->values[i])
      free(self->values[i]);
  }

  free(self);
  
}

bool hash_encode(Hash *self, String identifier)
{
  if(!identifier)
    return false;
  if(hash_contains(self, identifier))
    return false;
  self->values[hashcode(identifier)]->empty = false;
  strncpy(self->values[hashcode(identifier)]->key, identifier, _KEY_MAX_SIZE_);
}

static size_t hashcode(String identifier)
{
  size_t key = 5381;
  int c;

  while (c = *identifier++)
    key = c + ((key << 5) + key) + c; /* key * 33 + c */
  
  return key;
}

static bool hash_contains(Hash *self, String identifier)
{
  if(!self || !identifier)
    return false;
  return !(self->values[hashcode(identifier)]->empty);
}