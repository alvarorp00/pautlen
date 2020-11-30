/**
 * 
 *  HEADER
 * 
 * 
 */

#include "hash.h"

/**
 * Main hash structure
 */
struct _Hash {
  SymbolNode **values; /* Hash nodes which store info */
};

/* ----------------------- */

/* SELF FUNCTIONS DECLARATIONS */

static bool init_nodes(Hash *hash);

static size_t hashcode(String identifier);
static size_t linearProbing(Hash *self, String identifier);


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
  
  if(!self)
    return;

  for (i = 0; i < _DEF_HASHLEN_; i++)
  {
    if(self->values[i])
    {
      free(self->values[i]);
    }
  }

  free(self->values);

  free(self);
  
}

bool hash_encode(Hash *self, SymbolNode *sn)
{
  size_t hashed;
  
  if(!sn)
    return false;
  if(hash_contains(self, node_get_key(sn)))
    return false;

  hashed = linearProbing(self, node_get_key(sn));

  self->values[hashed] = sn;
  
  return true;
}

SymbolNode* hash_decode(Hash *self, String identifier)
{
  if(!hash_contains(self, identifier))
    return NULL;

  return self->values[linearProbing(self, identifier)];
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

static size_t linearProbing(Hash *self, String identifier)
{
  size_t hashed, val;
  size_t i;
  
  hashed = hashcode(identifier);
  val = hashed;

  if (self->values[hashed] == NULL)
    return hashed;
  else
    if (strcmp(node_get_key(self->values[val]), identifier) == 0)
      return hashed;

  for (i = 1; i < _DEF_HASHLEN_; i++)
  {
    val = (hashed + i)%_DEF_HASHLEN_;

    if(self->values[val] != NULL)
    {
      if(strcmp(node_get_key(self->values[val]), identifier) == 0)
        {
          return val;
        }
    }
    return val;
  }
  
  return i;
}

bool hash_contains(Hash *self, String identifier)
{
  size_t hashed;

  if(!self || !identifier)
    return false;

  hashed = linearProbing(self, identifier);

  fprintf(stdout, "VALUE HASHED: %ld\n", hashed);

  if(hashed == _DEF_HASHLEN_)
    return false;

  if(self->values[hashed] == NULL)
    return false;

  return (strcmp(node_get_key(self->values[hashed]), identifier) == 0);
}