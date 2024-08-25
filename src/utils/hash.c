#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAP_SIZE 10


typedef struct KeyValue2 {
    char *key;
    void *value;
} KeyValue2;

typedef struct HashMap2 {
    KeyValue2 table[MAP_SIZE];
} HashMap2;

/**
 *
 */
uint32_t hash2(const char *key) {
    uint32_t hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    return 31 * hash % MAP_SIZE;
}

/**
 *
 */
void put(HashMap2 *map, char *key, void *value) {
    uint32_t i = hash2(key);
    KeyValue2 kv = {
        .key = strdup(key),
        .value = value
    };
    map->table[i] = kv;
}

/**
 *
 */
void *get(HashMap2 map, char *key) {
    return map.table[hash2(key)].value;
}

/**
 *
 */
bool has(HashMap2 map, char *key) {
    return false;
}

/**
 *
 */
void create_map() {
    HashMap2 map;
    for (int i = 0; i < MAP_SIZE; i++) {
        map.table[i].key = NULL;
        map.table[i].value = NULL;
    }
    put(&map, "roi", "asdf");
    char *a = get(map, "roi");
    printf("%s\n", a);
}
