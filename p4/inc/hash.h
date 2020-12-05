#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h> /* for size_t */
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "symbol.h"

#define _DEF_HASHLEN_ 15
#define _CRITICAL_FACTOR_ 0.7

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
 * @param value stored value
 * @return if it was posible
 */
bool hash_encode(Hash *hash, void *value);

/**
 * Retrieves an element prev. stored in hash
 * @param hash where element is stored
 * @param value stored value
 * @return value retrieved
 */
void *hash_decode(Hash *hash, void *value);

/**
 * Deletes an existant value in hash
 * @param hash where element is stored
 * @param value value to be deleted
 * @return if was posible
 */
bool hash_deleteValue(Hash *hash, void* value);

/**
 * Cleans memory
 * @param hash structure to delete
 */
void hash_clean(Hash *hash);

/**
 * If value is stored
 * @param hash where value is stored
 * @param value value to check
 * @return if it's stored
 */
bool hash_contains(Hash *hash, void *value);

#endif