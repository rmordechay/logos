#include "HashMap.h"
#include <stdlib.h>
#include <string.h>


uint32_t hash(const char* key) {
    uint32_t h = HASH;
    while (*key) {
        h ^= (unsigned char)*key++;
        h *= FNV_PRIME;
    }
    return h % CAPACITY;
}

Entry* new_entry(HashMap* map, const char* key, const void* value) {
    Entry* entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = malloc(map->value_size);
    entry->next = NULL;
    memcpy(entry->value, value, map->value_size);
    return entry;
}

void Map_init(HashMap* map, const size_t value_size) {
    map->size = 0;
    map->value_size = value_size;
    map->buckets = calloc(CAPACITY, sizeof(Entry*));
}

void Map_add(HashMap* map, const char* key, const void* value) {
    const uint32_t index = hash(key);
    const Entry* current = map->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            memcpy(current->value, value, map->value_size);
            return;
        }
        current = current->next;
    }
    Entry* entry = new_entry(map, key, value);
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
    map->size++;
}

void* Map_get(const HashMap* map, const char* key) {
    const Entry* current = map->buckets[hash(key)];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void Map_delete(HashMap* map, const char* key) {
    const uint32_t index = hash(key);
    Entry* current = map->buckets[index];
    Entry* prev = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
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

void Map_free(HashMap* map) {
    for (size_t i = 0; i < CAPACITY; ++i) {
        Entry* current = map->buckets[i];
        while (current) {
            Entry* next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(map->buckets);
    free(map);
}
