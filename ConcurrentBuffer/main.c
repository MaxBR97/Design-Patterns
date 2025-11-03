#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "concurrentBuffer.h"

#define BUFFER_SIZE 100
#define NUM_WRITERS 3
#define NUM_READERS 2
#define ITEMS_PER_WRITER 20

ConcurrentBuffer *buffer;
int total_items_written = 0;
int total_items_read = 0;
pthread_mutex_t stats_lock = PTHREAD_MUTEX_INITIALIZER;

// Test 1: Simple enqueue and dequeue
void test_simple() {
    printf("\n=== Test 1: Simple Enqueue/Dequeue ===\n");
    buffer = constructor(BUFFER_SIZE);
    
    printf("Enqueuing: 1, 2, 3\n");
    buffer->enqueue(buffer, 1);
    buffer->enqueue(buffer, 2);
    buffer->enqueue(buffer, 3);
    
    printf("Dequeuing: %d, %d, %d\n", 
           buffer->dequeue(buffer),
           buffer->dequeue(buffer),
           buffer->dequeue(buffer));
    
    printf("✓ Test 1 passed\n");
}

// Writer thread function
void* writer_thread(void *arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < ITEMS_PER_WRITER; i++) {
        int value = thread_id * 1000 + i;
        printf("[Writer %d] Enqueuing: %d\n", thread_id, value);
        buffer->enqueue(buffer, value);
        
        pthread_mutex_lock(&stats_lock);
        total_items_written++;
        pthread_mutex_unlock(&stats_lock);
        
        // Random delay to simulate work
        usleep(rand() % 1000);
    }
    
    printf("[Writer %d] Finished\n", thread_id);
    free(arg);
    return NULL;
}

// Reader thread function
void* reader_thread(void *arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < (ITEMS_PER_WRITER * NUM_WRITERS) / NUM_READERS; i++) {
        int value = buffer->dequeue(buffer);
        printf("[Reader %d] Dequeued: %d\n", thread_id, value);
        
        pthread_mutex_lock(&stats_lock);
        total_items_read++;
        pthread_mutex_unlock(&stats_lock);
        
        // Random delay to simulate work
        usleep(rand() % 1000);
    }
    
    printf("[Reader %d] Finished\n", thread_id);
    free(arg);
    return NULL;
}

// Test 2: Concurrent read/write with multiple threads
void test_concurrent_read_write() {
    printf("\n=== Test 2: Concurrent Read/Write (Multiple Threads) ===\n");
    buffer = constructor(BUFFER_SIZE);
    
    pthread_t writers[NUM_WRITERS];
    pthread_t readers[NUM_READERS];
    
    total_items_written = 0;
    total_items_read = 0;
    
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&writers[i], NULL, writer_thread, thread_id);
    }
    
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&readers[i], NULL, reader_thread, thread_id);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    printf("\nTotal items written: %d\n", total_items_written);
    printf("Total items read: %d\n", total_items_read);
    
    if (total_items_written == total_items_read) {
        printf("✓ Test 2 passed: All items accounted for\n");
    } else {
        printf("✗ Test 2 failed: Mismatch in written/read items\n");
    }
}

// Stress test: Rapid enqueue/dequeue
void test_stress() {
    printf("\n=== Test 3: Stress Test (Rapid Operations) ===\n");
    buffer = constructor(BUFFER_SIZE);
    
    printf("Rapidly enqueuing %d items...\n", BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer->enqueue(buffer, i);
    }
    
    printf("Rapidly dequeuing %d items...\n", BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int val = buffer->dequeue(buffer);
        if (val != i) {
            printf("✗ Test 3 failed: Expected %d, got %d\n", i, val);
            return;
        }
    }
    
    printf("✓ Test 3 passed: All items in correct order\n");
}

// Test buffer wrapping
void test_buffer_wrapping() {
    printf("\n=== Test 4: Buffer Wrapping ===\n");
    buffer = constructor(5);
    
    // Fill and drain multiple times to test index wrapping
    for (int cycle = 0; cycle < 3; cycle++) {
        printf("Cycle %d:\n", cycle + 1);
        for (int i = 0; i < 5; i++) {
            buffer->enqueue(buffer, cycle * 100 + i);
        }
        
        for (int i = 0; i < 5; i++) {
            int val = buffer->dequeue(buffer);
            printf("  Dequeued: %d\n", val);
            if (val != cycle * 100 + i) {
                printf("✗ Test 4 failed at cycle %d\n", cycle);
                return;
            }
        }
    }
    
    printf("✓ Test 4 passed: Buffer wrapping works correctly\n");
}

// Main test runner
int main(int argc, char **argv) {
    printf("========================================\n");
    printf("  Concurrent Buffer Test Suite\n");
    printf("========================================\n");
    
    srand(time(NULL));
    
    test_simple();
    test_concurrent_read_write();
    test_stress();
    test_buffer_wrapping();
    
    printf("\n========================================\n");
    printf("  All tests completed\n");
    printf("========================================\n");
    
    return 0;
}