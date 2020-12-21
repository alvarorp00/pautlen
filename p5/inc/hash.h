#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h> /* for fast integers */
#include "prototypes.h"

#define _DEF_HASHLEN_ 9
#define _HIGH_CRITICAL_FACTOR_ 0.6

typedef struct _iterator_node_t iterator_node_t;
typedef struct _hash_iterator_t hash_iterator_t;

/**
 * Hash type definition
 */
typedef struct _hash_t hash_t;

/**
 * Initialize hash structure
 * @param hashcode hashcode function
 * @param equals equals function
 * @param clean clean funciton
 * @return hash
 */
hash_t *hash_init(hashcode_t hashcode, equals_t equals, clean_t clean);

/**
 * Stores an element in hash
 * @param hash where element will be stored
 * @param info stored info
 * @return if it was posible
 */
bool hash_encode(hash_t *hash, void *info);

/**
 * Retrieves an element prev. stored in hash
 * @param hash where element is stored
 * @param info stored info
 * @return info retrieved
 */
void *hash_decode(hash_t *hash, void *info);

/**
 * Cleans memory
 * @param hash structure to delete
 */
void hash_clean(hash_t *hash);

/**
 * If info is stored
 * @param hash where info is stored
 * @param info info to check
 * @return if it's stored
 */
bool hash_contains(hash_t *hash, void *info);

/**
 * Returns a hash iterator with NON-NULL values
 * @param hash with values
 * @return hash iterator
 */
hash_iterator_t *hash_iterate(hash_t *hash);

/**
 * Gets first hash_iterator node
 * @param iterator returned by hash_iterate()
 * @return first iterator node
 */
iterator_node_t *first(hash_iterator_t *iterator);

/**
 * Gets next iterator node's node
 * @param _inode whos next value's desired
 * @return next iterator node
 */
iterator_node_t *next(iterator_node_t *_inode);

/**
 * Gets iterator node info
 * @param _inode whose info is desired
 * @return info
 */
void *iter_nodeInfo(iterator_node_t *_inode);

/**
 * Returns if iterator node has
 * next node or node
 * @param _inode iterator node
 * @return if hash next or not
 */
bool hasNext(iterator_node_t *_inode);

/**
 * Cleans hash iterator
 * @param iterator hash iterator
 */
void hash_iterate_clean(hash_iterator_t *iterator);

#endif