/**
 * 
 * 
 * HEADER
 * 
 * 
 */

#include "symbol.h"

/**
 * Variable type definition
 */
typedef struct _Variable Variable;

/**
 * Parametre type definition
 */
typedef struct _Parametre Parametre;

/**
 * Function type definition
 */
typedef struct _Function Function;

/**
 * union with element stored
 */
typedef union _Element Element;

/**
 * Structure with alfa's variables info
 */
struct _Variable
{
  DataType dataType; /* Identifier data type {BOOLEAN, INT} */
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
  DataType dataType; /* Identifier data type {BOOLEAN, INT} */
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
  DataType returnType; /* Function return type */
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
struct _symbol_t {
  char key[MAX_LEN]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in struct {Function, Parametre, Variable} */
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
static bool symbol_set_key(symbol_t *s, String key);

/* ------------ */

symbol_t *symbol_init(String key, int value)
{
  symbol_t *s;

  if(!key)
    return NULL;

  if(!key || strlen(key) > MAX_LEN)
    return NULL;

  s = (symbol_t*)calloc(1, sizeof(symbol_t));

  if(!s)
    return NULL;

  symbol_set_key(s, key);
  
  if(value != NONE)
    s->value = value;

  return s;
}

void symbol_configure_scalar_variable(
  symbol_t *s,
  DataType dataType,
  Scope scope,
  int pos
)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = SCALAR;
  s->element.var.dataType = dataType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
}

void symbol_configure_vector_variable(
  symbol_t *s,
  DataType dataType,
  Scope scope,
  int pos,
  int8_t size
)
{
  if(!s)
    return;

  s->elemCat = VAR;
  s->element.var.classCat = VECTOR;
  s->element.var.dataType = dataType;
  s->element.var.scope = scope;
  s->element.var.pos = pos;
  s->element.var.size = size;
}

void symbol_configure_scalar_parametre(
  symbol_t *s,
  DataType dataType,
  int pos
)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = SCALAR;
  s->element.param.dataType = dataType;
  s->element.param.pos = pos;
}

void symbol_configure_vector_parametre(
  symbol_t *s,
  DataType dataType,
  int pos,
  int8_t size
)
{
  if(!s)
    return;
  s->elemCat = PARAM;
  s->element.param.classCat = VECTOR;
  s->element.param.dataType = dataType;
  s->element.param.pos = pos;
  s->element.param.size = size;
}

void symbol_configure_function(
  symbol_t *s,
  int32_t params,
  int32_t localvars,
  DataType returnType
)
{
  if(!s)
    return;
  s->elemCat = FUNCT;
  s->element.func.params = params;
  s->element.func.localvars = localvars;
  s->element.func.returnType = returnType;
}

String symbol_get_key(symbol_t *s)
{
  if(!s)
    return NULL;
  return s->key;
}

static bool symbol_set_key(symbol_t *s, String key)
{
  if(!s || !key)
    return false;

  if(strlen(key) > MAX_LEN)
    return false;

  strcpy(s->key, key);

  return true;
}

void symbol_set_category(symbol_t *s, ElementCategory elemCat)
{
  if(!s)
    return;
  s->elemCat = elemCat;
}

ElementCategory symbol_get_category(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;
  return s->elemCat;
}

int symbol_get_value(symbol_t *s)
{
  if(!s)
    return NONE;
  return s->value;
}

bool symbol_equals(symbol_t *s1, symbol_t *s2)
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

  s = (symbol_t*)s;

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

String symbol_toString(symbol_t *s)
{
  if(!s)
    return NULL;
  return s->key;
}

/* ------------------------------ */
/* -- -- -- - GETTERS -- -- -- -- */
/* ------------------------------ */

/* - - - COMMON - - - */

DataType symbol_blind_dataType(symbol_t *s)
{
  if(!s )
    return UNSP_ERR;
  if(symbol_get_category(s) == VAR)
    return s->element.var.dataType;
  else if (symbol_get_category(s) == PARAM)
    return s->element.param.dataType;
  else
    return s->element.func.returnType;
}

IdentifierCategory symbol_blind_identifierCategory(symbol_t *s)
{
  if(!s || symbol_get_category(s) == FUNCT)
    return UNSP_ERR;
  if(symbol_get_category(s) == VAR)
    return s->element.var.classCat;
  else
    return s->element.param.classCat;
}

int8_t symbol_blind_size(symbol_t *s)
{
  if (! s || symbol_get_category(s) == FUNCT)
    return CHAR_MIN;
  return symbol_get_category(s) == VAR ? 
    s->element.var.size : s->element.param.size;
}

Scope symbol_blind_scope(symbol_t *s)
{
  if(!s || symbol_get_category(s) == FUNCT)
    return NONE;
  return symbol_get_category( s ) == VAR ?
    s->element.var.scope : LOCAL;  
}

/*- - - VARS - - - */

DataType symbol_get_var_dataType(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;
  return s->element.var.dataType;
}

IdentifierCategory symbol_get_var_identifierCategory(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;
  return s->element.var.classCat;
}

Scope symbol_get_var_scope(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;
  return s->element.var.scope;
}

int symbol_get_var_pos(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;
  return s->element.var.pos;
}

int8_t symbol_get_var_size(symbol_t *s)
{
  if(!s)
    return CHAR_MIN;
  return s->element.var.size;
}

/* - - - PARAMS - - -  */

DataType symbol_get_param_dataType(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;

  return s->element.param.dataType;
}

IdentifierCategory symbol_get_param_identifierCategory(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;

  return s->element.param.classCat;
}

int symbol_get_param_pos(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;

  return s->element.param.pos;
}

int8_t symbol_get_param_size(symbol_t *s)
{
  if(!s)
    return CHAR_MIN;

  return s->element.param.size;
}

/* - - - FUNCTS - - - */

int32_t symbol_get_funct_params(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;

  return s->element.func.params;
}

int32_t symbol_get_funct_localvars(symbol_t *s)
{
  if(!s)
    return UNSP_ERR;

  return s->element.func.localvars;
}

DataType symbol_get_funct_returnType(symbol_t *s)
{
  return s != NULL ? s->element.func.returnType : NONE;
}

/*  - * - * - * - * - * - * - * - */

