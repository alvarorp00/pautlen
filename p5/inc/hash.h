#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define _DEF_HASHLEN_ 9
#define _HIGH_CRITICAL_FACTOR_ 0.6

/**
 * Hashcode Funct prototype
 * @param void elem to be compared
 * @return hashcode value
 */
typedef uint_fast64_t (*Hashcode)(void*);

/**
 * Equals Func prototype
 * @param void element 1
 * @param void element 2
 * @return Returns if both elements are equal
 */
typedef bool (*Equals)(void*, void*);

/**
 * Clean Func prototype
 * @param void element to clean
 */
typedef void (*Clean)(void*);

/**
 * Hash type definition
 */
typedef struct _Hash Hash;

/**
 * Initialize hash structure
 * @param hashcode hashcode function
 * @param equals equals function
 * @param clean clean funciton
 * @return hash
 */
Hash *hash_init(Hashcode hashcode, Equals equals, Clean clean);

/**
 * Stores an element in hash
 * @param hash where element will be stored
 * @param info stored info
 * @return if it was posible
 */
bool hash_encode(Hash *hash, void *info);

/**
 * Retrieves an element prev. stored in hash
 * @param hash where element is stored
 * @param info stored info
 * @return info retrieved
 */
void *hash_decode(Hash *hash, void *info);

/**
 * Cleans memory
 * @param hash structure to delete
 */
void hash_clean(Hash *hash);

/**
 * If info is stored
 * @param hash where info is stored
 * @param info info to check
 * @return if it's stored
 */
bool hash_contains(Hash *hash, void *info);

#endif