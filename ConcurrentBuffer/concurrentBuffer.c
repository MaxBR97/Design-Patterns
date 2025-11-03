#include "concurrentBuffer.h"
#include <semaphore.h>
#include <pthread.h>

void enqueue(void *concurrentBuffer, int x) {
    ConcurrentBuffer *obj = (ConcurrentBuffer*)concurrentBuffer;
    
    sem_wait(&obj->capacity);
    pthread_mutex_lock(&obj->writeLock);
    
    obj->elements[obj->writeIndex++] = x;
    if (obj->writeIndex >= obj->maxSize) {
        obj->writeIndex = 0;
    }
    
    pthread_mutex_unlock(&obj->writeLock);
    sem_post(&obj->size);
}

int dequeue(void *concurrentBuffer) {
    ConcurrentBuffer *obj = (ConcurrentBuffer*)concurrentBuffer;
    int ans;
    
    sem_wait(&obj->size);
    pthread_mutex_lock(&obj->readLock);
    
    ans = obj->elements[obj->readIndex++];
    if (obj->readIndex >= obj->maxSize) {
        obj->readIndex = 0;
    }
    
    pthread_mutex_unlock(&obj->readLock);
    sem_post(&obj->capacity);
    
    return ans;
}

ConcurrentBuffer* constructor(int bufferSize) {
    ConcurrentBuffer* obj = malloc(sizeof(ConcurrentBuffer));
    obj->elements = malloc(bufferSize * sizeof(int));
    obj->readIndex = 0;
    obj->writeIndex = 0;
    obj->maxSize = bufferSize;
    
    pthread_mutex_init(&obj->readLock, NULL);
    pthread_mutex_init(&obj->writeLock, NULL);
    sem_init(&obj->size, 0, 0);
    sem_init(&obj->capacity, 0, bufferSize);
    
    obj->enqueue = enqueue;
    obj->dequeue = dequeue;
    
    return obj;
}

