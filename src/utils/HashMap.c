#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 1024
const uint32_t FNV_PRIME = 16777619U;
const uint32_t HASH = 2166136261U;

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** buckets;
    uint32_t value_size;
} HashMap;

uint32_t hash(const char* key) {
    uint32_t hash = HASH;
    while (*key) {
        hash ^= (uint8_t)*key++;
        hash *= FNV_PRIME;
    }
    return hash % CAPACITY;
}

Entry* new_entry(HashMap* map, const char* key, const void* value) {
    Entry* entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = malloc(map->value_size);
    memcpy(entry->value, value, map->value_size);
    entry->next = NULL;
    return entry;
}

HashMap* Map_new_Int(const uint32_t value_size) {
    HashMap* map = malloc(sizeof(HashMap));
    map->value_size = value_size;
    map->buckets = calloc(CAPACITY, sizeof(Entry*));
    return map;
}

void Map_add_Map_Str_Any(HashMap* map, const char* key, const void* value) {
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
}

void* Map_get_Map_Str(const HashMap* map, const char* key) {
    const Entry* current = map->buckets[hash(key)];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void Map_free_Map(HashMap* map) {
    for (int i = 0; i < CAPACITY; i++) {
        Entry* current = map->buckets[i];
        while (current) {
            Entry* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

int main(void) {
    HashMap* map = Map_new_Int(sizeof(char*));
    const char* x = "kdjfh";
    Map_add_Map_Str_Any(map, "answer", &x);
    printf("Value: %s\n", *(char**)Map_get_Map_Str(map, "answer"));
    // Map_free_Map(map);
    return 0;
}
