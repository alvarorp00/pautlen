#include <math.h>
#include <string.h>
#include "hash.h"

#define _DEFAULT_LAMBDA 512
#define _BUFFER 512

struct _Hash
{
  char **values;
};

unsigned int hashed(int index);
bool empty(char *str);

Hash *hash_init(int size)
{
  unsigned int dim;
  unsigned int i;

  Hash *hash;

  dim = (size == _USE_DEFAULT) ? _DEFAULT_LAMBDA : size;

  hash = NULL;

  if((hash = (Hash*)malloc(1*sizeof(Hash))) == NULL)
    return NULL;

  hash->values = (char**)malloc(_DEFAULT_LAMBDA*sizeof(char*));
  if(!hash->values)
  {
    hash_destroy(hash);
    return NULL;
  }

  for(i = 0; i < _DEFAULT_LAMBDA; ++i)
  {
    hash->values[i] = NULL;
    hash->values[i] = (char*)malloc(_BUFFER*sizeof(char));
    if(!hash->values[i])
    {
      hash_destroy(hash);
      return NULL;
    }
    hash->values[i][0] = '\0';
  }

  return hash;
}


bool hash_encode(Hash *hash, int index, char* value)
{
  unsigned int pos;
  
  if(!value)
    return false;

  pos = hashed(index);

  if(!empty(hash->values[pos]))
    return false;

  strncpy(hash->values[pos], value, _BUFFER);

  return true;
}


char *hash_retrieve(Hash *hash, int index)
{
  unsigned int pos;

  pos = hashed(index);

  return hash->values[pos];
}


void hash_remove(Hash *hash, int index)
{
  unsigned int pos;

  pos = hashed(index);

  hash->values[pos][0] = '\0';
} 


void hash_destroy(Hash *hash)
{
  unsigned int i;
  
  if(!hash)
    return;

  for(i = 0; i < _DEFAULT_LAMBDA; ++i)
  {
    if(!hash->values[i])
      break;
    free(hash->values[i]);
  }

  free(hash->values);
  free(hash);
}


unsigned int hashed(int index)
{
  return (abs(index) % _DEFAULT_LAMBDA);
}


bool empty(char *str)
{
  return (str[0] == '\0');
}