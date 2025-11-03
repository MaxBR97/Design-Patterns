#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

struct ConcurrentBuffer;

typedef struct ConcurrentBuffer {
    int *elements;
    int readIndex;
    int writeIndex;
    int maxSize;
    sem_t size;      
    sem_t capacity;  
    pthread_mutex_t readLock;
    pthread_mutex_t writeLock;

    void (*enqueue)(void *, int);
    int (*dequeue)(void *);
} ConcurrentBuffer;

ConcurrentBuffer* constructor(int bufferSize);
void enqueue(void *concurrentBuffer, int x);
int dequeue(void *concurrentBuffer);