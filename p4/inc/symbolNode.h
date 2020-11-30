#ifndef _S_NODE_H_
#define _S_NODE_H_

#include "alfa.h"

typedef struct _Variable Variable;
typedef struct _Parametre Parametre;
typedef struct _Function Function;

typedef union _Element Element;

/**
 * Starts a new node_init structure
 */
SymbolNode* node_init(ElementCategory elemCat, String key);

/**
 * Returns node's key (String)
 */
String node_get_key(SymbolNode *sn);

/**
 * Sets node's key
 */
bool node_set_key(SymbolNode *sn, String key);

/**
 * Return true if both nodes are equal
 */
bool node_equals(SymbolNode *sn1, SymbolNode *sn2);

/**
 * Configures node as a scalar variable
 */
void node_configure_scalar_variable(SymbolNode *sn, DataType basicType, Scope scope, __u_short pos);

/**
 * Configures node as a vector variable
 */
void node_configure_vector_variable(SymbolNode *sn, DataType basictype, Scope scope, __u_short pos, __u_int size);

#endif