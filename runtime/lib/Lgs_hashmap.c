#include "Lgs_iterator.h"
#include "Lgs_helpers.h"
#include <string.h>
#include <stdlib.h>

#define MAP_CAPACITY 1024

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Lgs_Map_Entry;

typedef struct {
    Lgs_Map_Entry** buckets;
    size_t size;
    size_t value_size;
} Lgs_Hashmap;

static Lgs_Map_Entry* new_entry(Lgs_Hashmap* map, const char* key, const void* value) {
    Lgs_Map_Entry* entry = malloc(sizeof(Lgs_Map_Entry));
    entry->key = strdup(key);
    entry->value = malloc(map->value_size);
    entry->next = NULL;
    memcpy(entry->value, value, map->value_size);
    return entry;
}

static void free_entry(Lgs_Map_Entry* current) {
    free(current->key);
    free(current);
}

void Lgs_Map_init(Lgs_Hashmap* map, const size_t value_size) {
    if (value_size == 0 || value_size > 4096) exit(1);
    map->size = 0;
    map->value_size = value_size;
    map->buckets = calloc(MAP_CAPACITY, sizeof(void*));
}

void Lgs_Map_add(Lgs_Hashmap* map, const char* key, const void* value) {
    if (!key || strlen(key) > 1024) exit(1);
    const size_t index = Lgs_hash(key) % MAP_CAPACITY;
    Lgs_Map_Entry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, value, map->value_size);
            return;
        }
        entry = entry->next;
    }
    entry = new_entry(map, key, value);
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
    map->size++;
}

void* Lgs_Map_get(const Lgs_Hashmap* map, const char* key) {
    if (!key || strlen(key) > 1024) exit(1);
    const size_t index = Lgs_hash(key) % MAP_CAPACITY;
    const Lgs_Map_Entry* entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return entry->value;
        entry = entry->next;
    }
    Lgs_printError(key);
    Lgs_printError2();
    return NULL;
}

void Lgs_Map_delete(Lgs_Hashmap* map, const char* key) {
    if (!key || strlen(key) > 1024) exit(1);
    const size_t index = Lgs_hash(key) % MAP_CAPACITY;
    Lgs_Map_Entry* current = map->buckets[index];
    Lgs_Map_Entry* prev = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) prev->next = current->next;
            else map->buckets[index] = current->next;
            free_entry(current);
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

size_t Lgs_Map_len(const Lgs_Hashmap* map) {
    return map->size;
}

bool Lgs_Map_isEmpty(const Lgs_Hashmap* map) {
    return map->size == 0;
}

bool Lgs_Map_isNotEmpty(const Lgs_Hashmap* map) {
    return map->size != 0;
}

void Lgs_Map_free(const Lgs_Hashmap* map) {
    for (size_t i = 0; i < MAP_CAPACITY; ++i) {
        Lgs_Map_Entry* current = map->buckets[i];
        while (current) {
            Lgs_Map_Entry* next = current->next;
            free_entry(current);
            current = next;
        }
    }
    free(map->buckets);
}

bool Lgs_Map_hasNext(Lgs_Iterator* iter) {
    const Lgs_Hashmap* map = iter->container;
    if (iter->entry) return true;
    while (iter->current < MAP_CAPACITY) {
        if (map->buckets[iter->current]) {
            iter->entry = map->buckets[iter->current];
            return true;
        }
        iter->current++;
    }
    return false;
}

void* Lgs_Map_next(Lgs_Iterator* iter) {
    if (!Lgs_Map_hasNext(iter)) return NULL;
    Lgs_Map_Entry* entry = iter->entry;
    iter->entry = entry->next;
    if (!iter->entry) iter->current++;
    return entry;
}

void Lgs_Map_initIter(Lgs_Hashmap* map, Lgs_Iterator* iter) {
    iter->container = (void*)map;
    iter->current = 0;
    iter->entry = NULL;
    iter->hasNext = Lgs_Map_hasNext;
    iter->next = Lgs_Map_next;
    iter->reset = Lgs_Iterator_reset;
}
