/**
 * 
 * 
 * HEADER
 * 
 * 
 */

#include "symbolNode.h"

/**
 * Structure with alfa's variables info
 */
struct _Variable
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  Scope scope; /* Scope {LOCAL, GLOBAL} */
  __u_short pos; /* Position in function in case it's in LOCAL Scope */
  __u_int size; /* Size of the variable in case it's a VECTOR */
};

/**
 * Structure with alfa's parametres info
 */
struct _Parametre
{
  DataType basicType; /* Identifier data type {BOOLEAN, INT} */
  IdentifierCategory classCat; /* Structure category identifier {SCALAR, VECTOR} */
  __u_short pos; /* Position of the parametre in function call */
  __u_int size; /* Size of the parametre in case it's a VECTOR */
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
  char key[_KEY_MAX_SIZE_]; /* Key to access this element */
  ElementCategory elemCat; /* Type of element stored in union {Function, Parametre, Variable} */
  Element element; /* Element */
};

SymbolNode *node_init(ElementCategory elemCat, String key)
{
  SymbolNode *sn;

  sn = (SymbolNode*)calloc(1, sizeof(SymbolNode));

  if(!sn)
    return NULL;

  sn->elemCat = elemCat;
  node_set_key(sn, key);

  return sn;
}

void node_configure_scalar_variable(SymbolNode *sn, DataType basicType, Scope scope, __u_short pos)
{
  if(!sn)
    return;

  sn->elemCat = VAR;
  sn->element.var.classCat = SCALAR;
  sn->element.var.basicType = basicType;
  sn->element.var.scope = scope;
  sn->element.var.pos = pos;
  sn->element.var.size = 0;
}

void node_configure_vector_variable(SymbolNode *sn, DataType basicType, Scope scope, __u_short pos, __u_int size)
{
  if(!sn)
    return;

  sn->elemCat = VAR;
  sn->element.var.classCat = VECTOR;
  sn->element.var.basicType = basicType;
  sn->element.var.scope = scope;
  sn->element.var.pos = pos;
  sn->element.var.size = size;
}

void node_configure_scalar_parametre(SymbolNode *sn, DataType basicType, __u_short pos)
{
  if(!sn)
    return;
  sn->elemCat = PARAM;
  sn->element.param.classCat = SCALAR;
  sn->element.param.basicType = basicType;
  sn->element.param.pos = pos;
  sn->element.param.size = 0;
}

void node_configure_vector_parametre(SymbolNode *sn, DataType basicType, __u_short pos, __u_int size)
{
  if(!sn)
    return;
  sn->elemCat = PARAM;
  sn->element.param.classCat = VECTOR;
  sn->element.param.basicType = basicType;
  sn->element.param.pos = pos;
  sn->element.param.size = size;
}

void node_configure_function(SymbolNode *sn, __u_short params, __u_short localvars)
{
  if(!sn)
    return;
  sn->elemCat = FUNCT;
  sn->element.func.params = params;
  sn->element.func.localvars = localvars;
}

String node_get_key(SymbolNode *sn)
{
  if(!sn)
    return NULL;
  return sn->key;
}

bool node_set_key(SymbolNode *sn, String key)
{
  if(!sn)
    return false;

  if(strlen(key) > _KEY_MAX_SIZE_)
    return false;

  strcpy(sn->key, key);

  return true;
}

bool node_equals(SymbolNode *sn1, SymbolNode *sn2)
{
  if(!sn1 || !sn2)
    return false;

  return (strcmp(node_get_key(sn1), node_get_key(sn2)) == 0);
}
