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

typedef struct Node {
    Pair pair;
    struct Node *next;
} Node;

typedef struct ConcurrentHashMap {
    int capacity;
    size_t size;
    Node **elements;

    size_t ( *hash )(void *self, int key);
    void (*rehash)(void *self);
    bool (*put)(void *self, Pair pair);
    bool (*get)(void *self, int key, int *value);
    void (*delete)(void *self, int key);
    void (*print)(void *self);
} ConcurrentHashMap;

// Function declarations
void rehash(void *self, bool expand);
size_t hash(void *self, int key);
bool put(void *self, Pair pair);
bool get(void *self, int key, int *value);
void delete(void *self, int key);
void print(void *self);
ConcurrentHashMap* constructor(void);

#endif

