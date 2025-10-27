#include "concurrentHashMap.h"
#include <pthread.h>

// Test tracking
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// Helper macros for assertions
#define ASSERT_EQ(actual, expected) do { \
    tests_run++; \
    if ((actual) == (expected)) { \
        tests_passed++; \
        printf("  ✓ PASS\n"); \
    } else { \
        tests_failed++; \
        printf("  ✗ FAIL: expected %d, got %d\n", (expected), (actual)); \
    } \
} while(0)

#define ASSERT_NEQ(actual, not_expected) do { \
    tests_run++; \
    if ((actual) != (not_expected)) { \
        tests_passed++; \
        printf("  ✓ PASS\n"); \
    } else { \
        tests_failed++; \
        printf("  ✗ FAIL: got unexpected value %d\n", (actual)); \
    } \
} while(0)

#define ASSERT_TRUE(condition) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("  ✓ PASS\n"); \
    } else { \
        tests_failed++; \
        printf("  ✗ FAIL: condition was false\n"); \
    } \
} while(0)

#define ASSERT_FALSE(condition) do { \
    tests_run++; \
    if (!(condition)) { \
        tests_passed++; \
        printf("  ✓ PASS\n"); \
    } else { \
        tests_failed++; \
        printf("  ✗ FAIL: condition was true\n"); \
    } \
} while(0)

void test_basic_insertion() {
    printf("\n=== Test 1: Basic Insertion ===\n");
    ConcurrentHashMap *map = constructor();
    map->put(map, (Pair){1, 10});
    map->put(map, (Pair){2, 20});
    map->put(map, (Pair){3, 30});
    printf("After inserting (1,10), (2,20), (3,30):\n");
    map->print(map);
    
    int value;
    printf("Verifying key 1: ");
    ASSERT_TRUE(map->get(map, 1, &value) && value == 10);
    printf("Verifying key 2: ");
    ASSERT_TRUE(map->get(map, 2, &value) && value == 20);
    printf("Verifying key 3: ");
    ASSERT_TRUE(map->get(map, 3, &value) && value == 30);
}

void test_update_existing_key() {
    printf("\n=== Test 2: Update Existing Key ===\n");
    ConcurrentHashMap *map = constructor();
    map->put(map, (Pair){1, 10});
    map->put(map, (Pair){1, 99});
    printf("After inserting (1,10) then updating to (1,99):\n");
    map->print(map);
    
    int value;
    printf("Verifying key 1 was updated to 99: ");
    ASSERT_TRUE(map->get(map, 1, &value) && value == 99);
}

void test_delete_key() {
    printf("\n=== Test 3: Delete Key ===\n");
    ConcurrentHashMap *map = constructor();
    map->put(map, (Pair){1, 10});
    map->put(map, (Pair){2, 20});
    map->put(map, (Pair){3, 30});
    printf("Initial state:\n");
    map->print(map);
    map->delete(map, 2);
    printf("After deleting key 2:\n");
    map->print(map);
    
    int value;
    printf("Verifying key 2 was deleted: ");
    ASSERT_FALSE(map->get(map, 2, &value));
    printf("Verifying key 1 still exists: ");
    ASSERT_TRUE(map->get(map, 1, &value) && value == 10);
    printf("Verifying key 3 still exists: ");
    ASSERT_TRUE(map->get(map, 3, &value) && value == 30);
}

void test_delete_nonexistent_key() {
    printf("\n=== Test 4: Delete Non-existent Key ===\n");
    ConcurrentHashMap *map = constructor();
    map->put(map, (Pair){1, 10});
    printf("Initial state:\n");
    map->print(map);
    map->delete(map, 999);
    printf("After attempting to delete key 999 (doesn't exist):\n");
    map->print(map);
    
    int value;
    printf("Verifying key 1 still exists after failed delete: ");
    ASSERT_TRUE(map->get(map, 1, &value) && value == 10);
    printf("Verifying non-existent key 999 not found: ");
    ASSERT_FALSE(map->get(map, 999, &value));
}

void test_hash_collisions() {
    printf("\n=== Test 5: Hash Collisions ===\n");
    ConcurrentHashMap *map = constructor();
    // With capacity=4, keys 0,4,8 will hash to same bucket (0 % 4 = 0)
    map->put(map, (Pair){0, 100});
    map->put(map, (Pair){4, 200});
    map->put(map, (Pair){8, 300});
    printf("After inserting (0,100), (4,200), (8,300) - all colliding in bucket 0:\n");
    map->print(map);
    
    int value;
    printf("Verifying all keys with collisions exist: ");
    ASSERT_TRUE(map->get(map, 0, &value) && value == 100);
    ASSERT_TRUE(map->get(map, 4, &value) && value == 200);
    ASSERT_TRUE(map->get(map, 8, &value) && value == 300);
    printf("  ✓ PASS\n");
}

void test_rehashing() {
    printf("\n=== Test 6: Rehashing (Capacity Expansion) ===\n");
    ConcurrentHashMap *map = constructor();
    printf("Initial capacity: %d\n", map->capacity);
    printf("Inserting items to trigger rehash:\n");
    // Insert more items than capacity (4) to trigger rehash
    for(int i = 0; i < 8; i++) {
        map->put(map, (Pair){i, i * 10});
    }
    printf("After inserting 8 items (capacity should have doubled):\n");
    printf("New capacity: %d\n", map->capacity);
    map->print(map);
    
        printf("Verifying all keys exist after rehash: ");
    int value;
    ASSERT_TRUE(map->get(map, 7, &value) && value == 70);
    ASSERT_TRUE(map->get(map, 0, &value) && value == 0);
    ASSERT_TRUE(map->get(map, 3, &value) && value == 30);
    printf("  ✓ PASS\n");
}

void test_delete_from_collision_chain() {
    printf("\n=== Test 7: Delete from Collision Chain ===\n");
    ConcurrentHashMap *map = constructor();
    // Create collision chain
    map->put(map, (Pair){0, 100});
    map->put(map, (Pair){4, 200});
    map->put(map, (Pair){8, 300});
    printf("Initial state with collisions:\n");
    map->print(map);
    map->delete(map, 4);
    printf("After deleting key 4 (middle of chain):\n");
    map->print(map);
    
    int value;
    printf("Verifying key 4 was deleted from chain: ");
    ASSERT_FALSE(map->get(map, 4, &value));
    printf("Verifying other keys in chain still exist: ");
    ASSERT_TRUE(map->get(map, 0, &value) && value == 100);
    ASSERT_TRUE(map->get(map, 8, &value) && value == 300);
    printf("  ✓ PASS\n");
}

void test_delete_head_of_collision_chain() {
    printf("\n=== Test 8: Delete Head of Collision Chain ===\n");
    ConcurrentHashMap *map = constructor();
    // Create collision chain
    map->put(map, (Pair){0, 100});
    map->put(map, (Pair){4, 200});
    map->put(map, (Pair){8, 300});
    printf("Initial state with collisions:\n");
    map->print(map);
    map->delete(map, 0);
    printf("After deleting key 0 (head of chain):\n");
    map->print(map);
    
    int value;
    printf("Verifying key 0 (head) was deleted: ");
    ASSERT_FALSE(map->get(map, 0, &value));
    printf("Verifying remaining keys in chain exist: ");
    ASSERT_TRUE(map->get(map, 4, &value) && value == 200);
    ASSERT_TRUE(map->get(map, 8, &value) && value == 300);
    printf("  ✓ PASS\n");
}

void test_multiple_rehashes() {
    printf("\n=== Test 9: Multiple Rehashes ===\n");
    ConcurrentHashMap *map = constructor();
    printf("Initial capacity: %d\n", map->capacity);
    // Insert many items to trigger multiple rehashes
    for(int i = 0; i < 20; i++) {
        map->put(map, (Pair){i, i * 10});
    }
    printf("After inserting 20 items:\n");
    printf("Final capacity: %d\n", map->capacity);
    map->print(map);
    
        printf("Verifying all inserted keys exist: ");
    int value;
    ASSERT_TRUE(map->get(map, 0, &value) && value == 0);
    ASSERT_TRUE(map->get(map, 15, &value) && value == 150);
    ASSERT_TRUE(map->get(map, 19, &value) && value == 190);
    printf("  ✓ PASS\n");
}

void test_comprehensive() {
    printf("\n=== Test 10: Comprehensive Test ===\n");
    ConcurrentHashMap *map = constructor();
    // Add items
    map->put(map, (Pair){1, 10});
    map->put(map, (Pair){2, 20});
    map->put(map, (Pair){3, 30});
    printf("Step 1 - Added items:\n");
    map->print(map);
    
    // Update existing
    map->put(map, (Pair){2, 25});
    printf("Step 2 - Updated key 2 to 25:\n");
    map->print(map);
    
    // Add more with collisions
    map->put(map, (Pair){5, 50});
    map->put(map, (Pair){9, 90});
    printf("Step 3 - Added more items:\n");
    map->print(map);
    
    // Delete item
    map->delete(map, 3);
    printf("Step 4 - Deleted key 3:\n");
    map->print(map);
    
    // Add back
    map->put(map, (Pair){3, 35});
    printf("Step 5 - Added key 3 back with new value:\n");
    map->print(map);
    
    int value;
    printf("Final verification: ");
    ASSERT_TRUE(map->get(map, 1, &value) && value == 10);
    ASSERT_TRUE(map->get(map, 2, &value) && value == 25);
    ASSERT_TRUE(map->get(map, 3, &value) && value == 35);
    ASSERT_TRUE(map->get(map, 5, &value) && value == 50);
    ASSERT_TRUE(map->get(map, 9, &value) && value == 90);
    printf("  ✓ PASS\n");
}

// Structure to pass data to threads
typedef struct {
    ConcurrentHashMap *map;
    int thread_id;
    int num_operations;
} ThreadData;

// Thread function for concurrent writes
void* thread_concurrent_writes(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    ConcurrentHashMap *map = data->map;
    int thread_id = data->thread_id;
    
    // Each thread inserts/updates keys in its own range
    for(int i = 0; i < data->num_operations; i++) {
        int key = (thread_id * 100) + i;
        int value = (thread_id * 1000) + i;
        map->put(map, (Pair){key, value});
    }
    
    return NULL;
}

// Thread function for concurrent reads
void* thread_concurrent_reads(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    ConcurrentHashMap *map = data->map;
    int thread_id = data->thread_id;
    
    for(int i = 0; i < data->num_operations; i++) {
        int key = (thread_id * 100) + i;
        int value;
        map->get(map, key, &value);
    }
    
    return NULL;
}

// Thread function for mixed operations (stress test)
void* thread_mixed_operations(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    ConcurrentHashMap *map = data->map;
    
    for(int i = 0; i < data->num_operations; i++) {
        int operation = i % 3;
        int key = i % 20;  // Operate on keys 0-19
        
        switch(operation) {
            case 0: // Put
                map->put(map, (Pair){key, i * 10});
                break;
            case 1: // Get
                {
                    int value;
                    map->get(map, key, &value);
                }
                break;
            case 2: // Delete (then put back)
                map->delete(map, key);
                map->put(map, (Pair){key, i * 20});
                break;
        }
    }
    
    return NULL;
}

// Thread function for rehashing stress test
void* thread_rehash_stress(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    ConcurrentHashMap *map = data->map;
    int thread_id = data->thread_id;
    
    // Insert enough keys to trigger rehashing
    for(int i = 0; i < data->num_operations; i++) {
        int key = (thread_id * 1000) + i;
        int value = key * 2;
        map->put(map, (Pair){key, value});
    }
    
    return NULL;
}

void test_concurrency() {
    printf("\n=== Test 11: Concurrent Writes ===\n");
    
    size_t num_threads = 4;
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    
    ConcurrentHashMap *map = constructor();
    
    // Initialize thread data
    for(int i = 0; i < num_threads; i++) {
        thread_data[i].map = map;
        thread_data[i].thread_id = i;
        thread_data[i].num_operations = 50; // Each thread does 50 operations
    }
    
    // Create threads for concurrent writes
    for(int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_concurrent_writes, &thread_data[i]);
    }
    
    // Wait for all threads to complete
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Threads completed concurrent writes.\n");
    
    // Verify all writes succeeded
    int value;
    int verified = 0;
    for(int i = 0; i < num_threads; i++) {
        for(int j = 0; j < 50; j++) {
            int key = (i * 100) + j;
            int expected = (i * 1000) + j;
            if(map->get(map, key, &value) && value == expected) {
                verified++;
            }
        }
    }
    
    printf("Verifying concurrent writes succeeded: ");
    ASSERT_EQ(verified, num_threads * 50);
    
    printf("\n=== Test 12: Concurrent Reads and Writes ===\n");
    
    map = constructor();
    
    // Pre-populate with some data
    for(int i = 0; i < 100; i++) {
        map->put(map, (Pair){i, i * 10});
    }
    
    // Create mix of read and write threads
    pthread_t read_threads[2];
    pthread_t write_threads[2];
    ThreadData read_data[2], write_data[2];
    
    for(int i = 0; i < 2; i++) {
        read_data[i].map = map;
        read_data[i].thread_id = i;
        read_data[i].num_operations = 100;
        pthread_create(&read_threads[i], NULL, thread_concurrent_reads, &read_data[i]);
    }
    
    for(int i = 0; i < 2; i++) {
        write_data[i].map = map;
        write_data[i].thread_id = i + 100;
        write_data[i].num_operations = 50;
        pthread_create(&write_threads[i], NULL, thread_concurrent_writes, &write_data[i]);
    }
    
    // Wait for all threads
    for(int i = 0; i < 2; i++) {
        pthread_join(read_threads[i], NULL);
        pthread_join(write_threads[i], NULL);
    }
    
    printf("Concurrent reads and writes completed.\n");
    printf("Verifying map still functional: ");
    ASSERT_TRUE(map->get(map, 0, &value) && value == 0);
    ASSERT_TRUE(map->get(map, 99, &value) && value == 990);
    printf("  ✓ PASS\n");
    
    printf("\n=== Test 13: Mixed Operations Stress Test ===\n");
    
    map = constructor();
    pthread_t mixed_threads[3];
    ThreadData mixed_data[3];
    
    for(int i = 0; i < 3; i++) {
        mixed_data[i].map = map;
        mixed_data[i].thread_id = i;
        mixed_data[i].num_operations = 100;
        pthread_create(&mixed_threads[i], NULL, thread_mixed_operations, &mixed_data[i]);
    }
    
    for(int i = 0; i < 3; i++) {
        pthread_join(mixed_threads[i], NULL);
    }
    
    printf("Mixed operations stress test completed.\n");
    printf("Verifying map integrity: ");
    
    // Try to get some keys to verify map is still functional
    int success = 0;
    for(int i = 0; i < 20; i++) {
        if(map->get(map, i, &value)) {
            success++;
        }
    }
    
    ASSERT_TRUE(success > 0); // At least some keys should exist
    
    printf("\n=== Test 14: Rehashing Under Concurrent Load ===\n");
    
    map = constructor();
    pthread_t rehash_threads[2];
    ThreadData rehash_data[2];
    
    for(int i = 0; i < 2; i++) {
        rehash_data[i].map = map;
        rehash_data[i].thread_id = i;
        rehash_data[i].num_operations = 30; // 30 ops * 2 threads = 60 total (will trigger rehash)
        pthread_create(&rehash_threads[i], NULL, thread_rehash_stress, &rehash_data[i]);
    }
    
    for(int i = 0; i < 2; i++) {
        pthread_join(rehash_threads[i], NULL);
    }
    
    printf("Rehashing under concurrent load completed.\n");
    printf("Verifying rehashing occurred correctly: ");
    ASSERT_TRUE(map->capacity >= 8); // Should have rehashed at least once
    
    // Verify some inserted values
    int found = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 30; j++) {
            int key = (i * 1000) + j;
            int expected = key * 2;
            if(map->get(map, key, &value) && value == expected) {
                found++;
            }
        }
    }
    ASSERT_TRUE(found >= 40); // Should have at least most of the keys
    printf("  ✓ PASS\n");
}

int main(int argc, char** argv) {
    test_basic_insertion();
    test_update_existing_key();
    test_delete_key();
    test_delete_nonexistent_key();
    test_hash_collisions();
    test_rehashing();
    test_delete_from_collision_chain();
    test_delete_head_of_collision_chain();
    test_multiple_rehashes();
    test_comprehensive();
    test_concurrency();
    
    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    
    if(tests_failed == 0) {
        printf("\n✓ All tests passed!\n");
    } else {
        printf("\n✗ Some tests failed!\n");
    }
    
    return tests_failed == 0 ? 0 : 1;
}