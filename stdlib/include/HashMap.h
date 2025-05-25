#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

#define CAPACITY 128
#define HASH 2166136261u
#define FNV_PRIME 16777619
#define MAX_STR_LEN 1024

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** buckets;
    size_t size;
    uint32_t value_size;
} HashMap;

void Map_init(HashMap* map, size_t value_size);
void Map_add(HashMap* map, const char* key, const void* value);
void* Map_get(const HashMap* map, const char* key);
size_t Map_len(const HashMap* map);
void Map_free(HashMap* map);

#endif //HASHMAP_H
