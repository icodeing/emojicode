//
//  EmojicodeDictionary.h
//  Emojicode
//
//  Created by Theo Weidmann on 19/04/15.
//  Copyright (c) 2015 Theo Weidmann. All rights reserved.
//

#ifndef EmojicodeDictionary_h
#define EmojicodeDictionary_h

#include "String.h"

namespace Emojicode {

/** Default initial capacity. MUST be a power of two, default: 8 */
#define DICTIONARY_DEFAULT_INITIAL_CAPACITY (1 << 3)

/** Factor for determining whether the dictionary should be resized. */
#define DICTIONARY_DEFAULT_LOAD_FACTOR (0.75f)

#define DICTIONARY_MAXIMUM_CAPACTIY (1 << 30)

#define DICTIONARY_MAXIMUM_CAPACTIY_THRESHOLD (1 << 16)

typedef uint64_t EmojicodeDictionaryHash;

/** The datastructure with the key-value pair */
typedef struct {
    /** The user specified key. */
    Object *key;
    
    /** The user specified value. */
    Box value;
    
    /** The cached hash for the key. Calculated on item addition. */
    EmojicodeDictionaryHash hash;
    
    /** EmojicodeDictionary stores a bucket's elements in a linked list. */
    Object *next;
    
} EmojicodeDictionaryNode;

/** Structure for the Emojicode standard Dictionary. The implementation is similar to Java's Hashmap. */
typedef struct {
    /** An array with pointers to linked lists. Initializes when the first item is inserted. */
    Object *buckets;
    
    /** Length of buckets array. */
    size_t bucketsCounter;
    
    /** The number of items stored in this dictionary. Used for determining whether to resize. */
    size_t size;
    
    /** When size * loadFactor >= bucketsCounter the dictionary doubles the amount of buckets */
    float loadFactor;
    
    /** Stores the next threshold for resizing. Is 0 until first resize when item is inserted. */
    size_t nextThreshold;
} EmojicodeDictionary;

void dictionaryPutVal(Object *dicto, Object *key, Box value, Thread *thread);

/** Remove an item by keyString as key */
void dictionaryRemove(EmojicodeDictionary *dict, Object *key, Thread *thread);

/** Get an item by keyString as key */
Value dictionaryLookup(EmojicodeDictionary *dict, Object *key, Thread *thread);

/** Check whether a key is in the dictionary */
bool dictionaryContains(EmojicodeDictionary *dict, Object *key);

void dictionaryMark(Object *dict);

void initDictionaryBridge(Thread *thread, Value *destination);

/** @warning GC-invoking */
void dictionaryInit(EmojicodeDictionary *dict);

void bridgeDictionarySet(Thread *thread, Value *destination);
void bridgeDictionaryGet(Thread *thread, Value *destination);
void bridgeDictionaryRemove(Thread *thread, Value *destination);
void bridgeDictionaryKeys(Thread *thread, Value *destination);
void bridgeDictionaryClear(Thread *thread, Value *destination);
void bridgeDictionaryContains(Thread *thread, Value *destination);
void bridgeDictionarySize(Thread *thread, Value *destination);

}

#endif /* EmojicodeDictionary_h */
