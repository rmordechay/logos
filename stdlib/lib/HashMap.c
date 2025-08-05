#include "Iterator.h"
#include "Runtime.h"
#include "Str.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAP_CAPACITY 1024

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

static Entry* new_entry(HashMap* map, const char* key, const void* value) {
    Entry* entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = malloc(map->value_size);
    entry->next = NULL;
    memcpy(entry->value, value, map->value_size);
    return entry;
}

static void free_entry(Entry* current) {
    free(current->key);
    free(current);
}

void Map_init(HashMap* map, const size_t value_size) {
    map->size = 0;
    map->value_size = value_size;
    map->buckets = calloc(MAP_CAPACITY, sizeof(void*));
}

void Map_add(HashMap* map, const char* key, const void* value) {
    const size_t index = Str_hash(key);
    Entry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, value, map->value_size);
            return;
        }
        entry = entry->next;
    }
    entry = new_entry(map, key, value);
    map->buckets[index] = entry;
    map->size++;
}

void* Map_get(const HashMap* map, const char* key) {
    const size_t index = Str_hash(key);
    const Entry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    char buffer[512];
    sprintf(buffer, "Error: %s not found\n", key);
    fprintf(stderr, "%s\n", buffer);
    return NULL;
}

void Map_delete(HashMap* map, const char* key) {
    const size_t index = Str_hash(key);
    Entry* current = map->buckets[index];
    Entry* prev = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free_entry(current);
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

size_t Map_len(const HashMap* map) {
    return map->size;
}

bool Map_isEmpty(const HashMap* map) {
    return map->size == 0;
}

bool Map_isNotEmpty(const HashMap* map) {
    return map->size != 0;
}

void Map_free(const HashMap* map) {
    for (size_t i = 0; i < MAP_CAPACITY; ++i) {
        Entry* current = map->buckets[i];
        while (current) {
            Entry* next = current->next;
            free_entry(current);
            current = next;
        }
    }
    free(map->buckets);
}

bool Map_hasNext(Iterator* iter) {
    const HashMap* map = iter->container;
    if (iter->entry != NULL) return true;
    while (iter->current < MAP_CAPACITY) {
        if (map->buckets[iter->current] != NULL) {
            iter->entry = map->buckets[iter->current];
            return true;
        }
        iter->current++;
    }
    return false;
}

void* Map_next(Iterator* iter) {
    if (!Map_hasNext(iter)) return NULL;
    Entry* entry = iter->entry;
    iter->entry = entry->next;
    if (iter->entry == NULL) {
        iter->current++;
    }
    return entry;
}

void Map_initIter(HashMap* map, Iterator* iter) {
    iter->container = (void*)map;
    iter->current = 0;
    iter->entry = NULL;
    iter->hasNext = Map_hasNext;
    iter->next = Map_next;
    iter->reset = Iter_reset;
}
