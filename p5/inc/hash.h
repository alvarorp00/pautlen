#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h> /* for fast integers */

#define _DEF_HASHLEN_ 9
#define _HIGH_CRITICAL_FACTOR_ 0.6

typedef struct _iterator_node_t iterator_node_t;
typedef struct _hash_iterator_t hash_iterator_t;

/**
 * hashcode_t Funct prototype
 * @param void elem to be compared
 * @return hashcode value
 */
typedef uint_fast64_t (*hashcode_t)(void*);

/**
 * equals_t Func prototype
 * @param void element 1
 * @param void element 2
 * @return Returns if both elements are equal
 */
typedef bool (*equals_t)(void*, void*);

/**
 * clean_t Func prototype
 * @param void element to clean
 */
typedef void (*clean_t)(void*);

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

hash_iterator_t *hash_iterate(hash_t *hash);
iterator_node_t *first(hash_iterator_t *iterator);
iterator_node_t *next(iterator_node_t *_inode);
void *iter_nodeInfo(iterator_node_t *_inode);
bool hasNext(iterator_node_t *_inode);
void hash_iterate_clean(hash_iterator_t *iterator);

#endif