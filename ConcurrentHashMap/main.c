#include "concurrentHashMap.h"

int main(int argc, char** argv) {
    ConcurrentHashMap *map = constructor();
    map->put(map, (Pair){1, 10});
    map->put(map, (Pair){2, 20});
    map->put(map, (Pair){3, 30});
    map->put(map, (Pair){4, 40});
    map->put(map, (Pair){5, 50});
    map->print(map);
    return 0;
}