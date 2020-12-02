/**
 * 
 * 
 * HEADER
 * 
 * 
 */

#include "symbol.h"

/**
 * Structure that stores scalar value or vector length
 */
union _Data
{
  __u_int size; /* Size of the parametre in case it's a VECTOR */
  int value; /* Value if it's scalar */
};


/**
 * Structure with alfa's variables info
 */
struct _Variable
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  Scope scope; /* Scope {LOCAL, GLOBAL} */
  __u_short pos; /* Position in function in case it's in LOCAL Scope */
  Data data; /* Size for vector, Value for Scalar */
};

/**
 * Structure with alfa's parametres info
 */
struct _Parametre
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  __u_short pos; /* Position of the parametre in function call */
  Data data; /* Size for vector, Value for Scalar */
};

/**
 * Structure with alfa's functions info
 */
struct _Function
{
  __u_short params; /* Number of function parametres */
  __u_short localvars; /* Number of function local variables */
  int value;
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
struct _Symbol {
  char key[_KEY_MAX_SIZE_]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in union {Function, Parametre, Variable} */
  Element element; /* Element */
};

Symbol *symbol_init(ElementCategory elemCat, String key)
{
  Symbol *s;

  s = (Symbol*)calloc(1, sizeof(Symbol));

  if(!s)
    return NULL;

  s->elemCat = elemCat;
  symbol_set_key(s, key);

  return s;
}

void symbol_configure_scalar_variable(Symbol *s, DataType basicType, Scope scope, __u_short pos, int value)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = SCALAR;
  s->element.var.basicType = basicType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
  s->element.var.data.value = value;
}

void symbol_configure_vector_variable(Symbol *s, DataType basicType, Scope scope, __u_short pos, __u_int size)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = VECTOR;
  s->element.var.basicType = basicType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
  s->element.var.data.size = size;
}

void symbol_configure_scalar_parametre(Symbol *s, DataType basicType, __u_short pos, int value)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = SCALAR;
  s->element.param.basicType = basicType;
  s->element.param.pos = pos;
  s->element.param.data.value = value;
}

void symbol_configure_vector_parametre(Symbol *s, DataType basicType, __u_short pos, __u_int size)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = VECTOR;
  s->element.param.basicType = basicType;
  s->element.param.pos = pos;
  s->element.param.data.size = size;
}

void symbol_configure_function(Symbol *s, __u_short params, __u_short localvars, int value)
{
  if(!s)
    return;
  s->elemCat = FUNCT;
  s->element.func.params = params;
  s->element.func.localvars = localvars;
  s->element.func.value = value;
}

String symbol_get_key(Symbol *s)
{
  if(!s)
    return NULL;
  return s->key;
}

bool symbol_set_key(Symbol *s, String key)
{
  if(!s)
    return false;

  if(strlen(key) > _KEY_MAX_SIZE_)
    return false;

  strcpy(s->key, key);

  return true;
}

bool symbol_equals(Symbol *s1, Symbol *s2)
{
  if(!s1 || !s2)
    return false;

  return (strcmp(symbol_get_key(s1), symbol_get_key(s2)) == 0);
}

size_t symbol_hashcode(void *s)
{
  size_t hashed = 5381;
  String identifier;
  int c;

  s = (Symbol*)s;

  identifier = symbol_get_key(s);

  while ((c = *identifier++) != '\0')
    hashed = c + ((hashed << 5) + hashed) + c; /* hashed * 33 + c */
  
  return hashed;
}

void symbol_delete(void *s)
{
  if(!s)
    return;
  free(s);
}
