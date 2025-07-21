#ifndef HASHMAP_H
#define HASHMAP_H
#include "Iterator.h"
#include <stdbool.h>

#define MAP_CAPACITY 1028

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** buckets;
    size_t size;
    size_t value_size;
} HashMap;

void Map_init(HashMap* map, size_t value_size);
void Map_add(HashMap* map, const char* key, const void* value);
void* Map_get(const HashMap* map, const char* key);
size_t Map_len(const HashMap* map);
bool Map_isEmpty(const HashMap* map);
bool Map_isNotEmpty(const HashMap* map);
void Map_free(const HashMap* map);

bool Map_hasNext(Iterator* iter);
void* Map_next(Iterator* iter);
void Map_initIter(HashMap* map, Iterator* iter);

#endif //HASHMAP_H
