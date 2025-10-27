#include "concurrentHashMap.h"

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
    
    printf("Verifying capacity doubled: ");
    ASSERT_EQ(map->capacity, 8);
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
    
    printf("Verifying capacity expanded correctly: ");
    ASSERT_EQ(map->capacity, 32);
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