/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"

typedef struct _SymbolNode SymbolNode;
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
struct _SymbolNode {
  bool empty; /* To control if this node is empty or not */
  char key[_KEY_MAX_SIZE_]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in union {Function, Parametre, Variable} */
  Element element; /* Element */
};

/**
 * Main hash structure
 */
struct _Hash {
  SymbolNode **values; /* Hash nodes which store info */
};

/* ----------------------- */

/* SELF FUNCTIONS DECLARATIONS */

static bool init_nodes(Hash *hash);
static bool init_node(Hash *hash, size_t hashed, String identifier);

static bool hash_contains(Hash *self, String identifier);

static size_t hashcode(String identifier);
static size_t quadraticProbing(Hash *self, String identifier);


/* ----------------------- */

Hash *hash_init()
{
  Hash *hash;

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
  if(!hash)
    return false;

  hash->values = (SymbolNode**)calloc(_DEF_HASHLEN_, sizeof(SymbolNode*));

  return true;
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
  size_t hashed;
  
  if(!identifier)
    return false;
  if(strlen(identifier) > _KEY_MAX_SIZE_)
    return false;
  if(hash_contains(self, identifier))
    return false;

  hashed = quadraticProbing(self, identifier);
  
  return init_node(self, hashed, identifier);
}

void* hash_decode(Hash *self, String identifier)
{
  if(!hash_contains(self, identifier))
    return NULL;

  fprintf(stdout, "IT'S OK!");

  return self->values[quadraticProbing(self, identifier)];
}

static size_t hashcode(String identifier)
{
  size_t hashed = 5381;
  int c;

  while ((c = *identifier++) != '\0')
    hashed = c + ((hashed << 5) + hashed) + c; /* hashed * 33 + c */
  
  hashed = hashed % _DEF_HASHLEN_;
  
  return hashed;
}

static size_t quadraticProbing(Hash *self, String identifier)
{
  size_t hashed, val;
  size_t i;
  
  hashed = hashcode(identifier);
  val = hashed;

  if (self->values[hashed] == NULL)
    return hashed;
  else
    if (strcmp(self->values[val]->key, identifier) == 0)
      return hashed;

  for (i = 1; i < _DEF_HASHLEN_; i++)
  {
    val = (hashed + i*i)%_DEF_HASHLEN_;

    if(self->values[val] != NULL)
    {
      if(strcmp(self->values[val]->key, identifier) == 0)
        {
          return val;
        }
    }
    return val;
  }
  
  return i;
}

static bool hash_contains(Hash *self, String identifier)
{
  size_t hashed;

  if(!self || !identifier)
    return false;

  hashed = quadraticProbing(self, identifier);

  fprintf(stdout, "VALUE HASHED: %ld\n", hashed);

  if(hashed == _DEF_HASHLEN_)
    return false;

  if(self->values[hashed] == NULL)
    return false;

  return (strcmp(self->values[hashed]->key, identifier) == 0);
}


static bool init_node(Hash *hash, size_t hashed, String identifier)
{
  if(!hash || !identifier)
    return false;

  if(hash->values[hashed] != NULL)
    return false;
  
  hash->values[hashed] = (SymbolNode*)calloc(1, sizeof(SymbolNode));

  if(hash->values[hashed] == NULL)
    return false;

  strcpy(hash->values[hashed]->key, identifier);

  return true;
}