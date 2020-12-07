/**
 * 
 * 
 * HEADER
 * 
 * 
 */

#include "symbol.h"

/**
 * Structure with alfa's variables info
 */
struct _Variable
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  Scope scope; /* Scope {LOCAL, GLOBAL} */
  int pos; /* Position in function in case it's in LOCAL Scope */
  int8_t size; /* Size in case it's a vector */
};

/**
 * Structure with alfa's parametres info
 */
struct _Parametre
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  int pos; /* Position of the parametre in function call */
  int8_t size; /* Size in case it's a vector */
};

/**
 * Structure with alfa's functions info
 */
struct _Function
{
  int32_t params; /* Number of function parametres */
  int32_t localvars; /* Number of function local variables */
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
  char key[MAX_LEN]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in union {Function, Parametre, Variable} */
  Element element; /* Element */
  int value; /* Element's associated value */
};

/* Local Functs */

/**
 * Static local function that sets key to given symbol
 * @param s symbol
 * @param key identifier
 * @return if ok
 */
static bool symbol_set_key(Symbol *s, String key);

/* ------------ */

Symbol *symbol_init(String key, int value)
{
  Symbol *s;

  if(!key)
    return NULL;

  if(!key || strlen(key) > MAX_LEN)
    return NULL;

  s = (Symbol*)calloc(1, sizeof(Symbol));

  if(!s)
    return NULL;

  symbol_set_key(s, key);
  
  if(value != NONE)
    s->value = value;

  return s;
}

void symbol_configure_scalar_variable(
  Symbol *s,
  DataType basicType,
  Scope scope,
  int pos
)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = SCALAR;
  s->element.var.basicType = basicType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
}

void symbol_configure_vector_variable(
  Symbol *s,
  DataType basicType,
  Scope scope,
  int pos,
  int8_t size
)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = VECTOR;
  s->element.var.basicType = basicType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
  s->element.var.size = size;
}

void symbol_configure_scalar_parametre(
  Symbol *s,
  DataType basicType,
  int pos
)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = SCALAR;
  s->element.param.basicType = basicType;
  s->element.param.pos = pos;
}

void symbol_configure_vector_parametre(
  Symbol *s,
  DataType basicType,
  int pos,
  int8_t size
)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = VECTOR;
  s->element.param.basicType = basicType;
  s->element.param.pos = pos;
  s->element.param.size = size;
}

void symbol_configure_function(
  Symbol *s,
  int32_t params,
  int32_t localvars
)
{
  if(!s)
    return;
  s->elemCat = FUNCT;
  s->element.func.params = params;
  s->element.func.localvars = localvars;
}

String symbol_get_key(Symbol *s)
{
  if(!s)
    return NULL;
  return s->key;
}

static bool symbol_set_key(Symbol *s, String key)
{
  if(!s || !key)
    return false;

  if(strlen(key) > MAX_LEN)
    return false;

  strcpy(s->key, key);

  return true;
}

void symbol_set_category(Symbol *s, ElementCategory elemCat)
{
  if(!s)
    return;
  s->elemCat = elemCat;
}

ElementCategory symbol_get_category(Symbol *s)
{
  if(!s)
    return UNSP_ERR;
  return s->elemCat;
}

int symbol_get_value(Symbol *s)
{
  if(!s)
    return NONE;
  return s->value;
}

bool symbol_equals(Symbol *s1, Symbol *s2)
{
  if(!s1 || !s2)
    return false;

  return (strcmp(symbol_get_key(s1), symbol_get_key(s2)) == 0);
}

uint_fast64_t symbol_hashcode(void *s)
{
  uint_fast64_t hashed = 5381;
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

String symbol_toString(Symbol *s)
{
  if(!s)
    return NULL;
  return s->key;
}
