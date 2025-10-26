#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct Pair {
    int key;
    int val;
} Pair;

typedef struct ConcurrentHashMap {
    int capacity;
    size_t size;
    Pair **elements;

    // void (*constructor)(void *self);
    size_t ( *hash )(void *self, int key);
    bool (*put)(void *self, Pair pair);
    void (*delete)(void *self, int key);
    void (*print)(void *self);
} ConcurrentHashMap;

// Forward declarations
size_t hash(void *self, int key);
bool put(void *self, Pair pair);
void delete(void *self, int key);
void print(void *self);
ConcurrentHashMap* constructor(void);

size_t hash(void *self, int key){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    return key % map->capacity;
}

bool put(void *self, Pair pair){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    size_t index = map->hash(self, pair.key);
    map->elements[index] = malloc(sizeof(Pair));
    *map->elements[index] = pair;
    return true;
}

void delete(void *self, int key){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    size_t index = map->hash(self, key);
    if(map->elements[index] != NULL){
        free(map->elements[index]);
        map->elements[index] = NULL;
    }
}

void print(void *self){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    for(int i = 0; i < map->capacity; i++){
        if(map->elements[i] != NULL){
            printf("(%d, %d) ", map->elements[i]->key, map->elements[i]->val);
        }
    }
    printf("\n");
}

ConcurrentHashMap* constructor() {
    ConcurrentHashMap *map = malloc(sizeof(ConcurrentHashMap));
    map->capacity = 10;
    map->size = 0;
    map->elements = (Pair**)calloc(10, sizeof(Pair*));
    map->hash = &hash;
    map->put = &put;
    map->delete = &delete;
    map->print = &print;
    return map;
}
