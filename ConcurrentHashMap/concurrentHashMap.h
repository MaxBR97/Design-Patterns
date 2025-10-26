#ifndef CONCURRENT_HASHMAP_H
#define CONCURRENT_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct Pair {
    int key;
    int val;
} Pair;

typedef struct ConcurrentHashMap {
    int capacity;
    size_t size;
    Pair **elements;

    size_t ( *hash )(void *self, int key);
    bool (*put)(void *self, Pair pair);
    void (*delete)(void *self, int key);
    void (*print)(void *self);
} ConcurrentHashMap;

// Function declarations
size_t hash(void *self, int key);
bool put(void *self, Pair pair);
void delete(void *self, int key);
void print(void *self);
ConcurrentHashMap* constructor(void);

#endif

