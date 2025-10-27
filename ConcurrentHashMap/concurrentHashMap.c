#include "concurrentHashMap.h"
#include <string.h>

size_t hash(void *self, int key){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    return key % map->capacity;
}

void rehash(void *self, bool expand){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    if(expand) {
        map->capacity *= 2;
        map->elements = realloc(map->elements, sizeof(typeof(map->elements)) * map->capacity);
        for (int i = map->capacity/2; i < map->capacity; i++){
            map->elements[i] = NULL;
        }

        for(int i = 0; i < map->capacity / 2; i++){
            Node *cur = map->elements[i];
            while(cur != NULL){
                Pair tmp;
                memcpy(&tmp, &(cur->pair), sizeof(Pair));
                Node* nextCur = cur->next;
                delete(self, cur->pair.key);
                put(self, tmp);
                cur = nextCur;
            }
        }
    } else {
        // Code here for shrinking the size of the hash map
    }

}

bool put(void *self, Pair pair){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    if(map->size >= map->capacity){
        rehash(self, true);
    }
    size_t index = map->hash(self, pair.key);
    if(map->elements[index] == NULL){
        map->elements[index] = malloc(sizeof(Node));
        map->elements[index]->pair = pair;
        map->elements[index]->next = NULL;
    } else {
        Node *cur = map->elements[index];
        Node *prev = NULL;
        while(cur != NULL && cur->pair.key != pair.key){
            prev = cur;
            cur = cur->next;
        }
        if(cur == NULL){
            Node *new_node = malloc(sizeof(Node));
            new_node->pair = pair;
            new_node->next = NULL;
            if(prev != NULL){
                prev->next = new_node;
            }
        } else {
            cur->pair = pair;
        }
    }
    map->size ++;

    return true;
}

bool get(void *self, int key, int *value){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    size_t index = map->hash(self, key);
    
    Node *cur = map->elements[index];
    while(cur != NULL){
        if(cur->pair.key == key){
            *value = cur->pair.val;
            return true;
        }
        cur = cur->next;
    }
    
    return false;
}

void delete(void *self, int key){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    size_t index = map->hash(self, key);
    
    if(map->elements[index] == NULL){
        return;
    }
    
    Node *cur = map->elements[index];
    Node *prev = NULL;
    
    while(cur != NULL && cur->pair.key != key){
        prev = cur;
        cur = cur->next;
    }
    
    if(cur != NULL){
        if(prev == NULL){
            map->elements[index] = cur->next;
        } else {
            prev->next = cur->next;
        }
        free(cur);
        map->size --;
    }
}

void print(void *self){
    ConcurrentHashMap *map = (ConcurrentHashMap*)self;
    for(int i = 0; i < map->capacity; i++){
        Node *cur = map->elements[i];
        while(cur != NULL){
            printf("(%d, %d) ", cur->pair.key, cur->pair.val);
            cur = cur->next;
        }
    }
    printf("\n");
}

ConcurrentHashMap* constructor() {
    ConcurrentHashMap *map = malloc(sizeof(ConcurrentHashMap));
    map->capacity = 4;
    map->size = 0;
    map->elements = (Node**)calloc(map->capacity, sizeof(Node*));
    map->hash = &hash;
    map->put = &put;
    map->get = &get;
    map->delete = &delete;
    map->print = &print;
    return map;
}
