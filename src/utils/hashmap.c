#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "hashmap.h"
#include "project/project.h"

/**
 *
 */
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % TABLE_SIZE;
}

/**
 *
 */
HashMap* create_hash_map() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

/**
 *
 */
void insert(HashMap* map, const char* key, void *value) {
    unsigned int index = hash(key);
    KeyValue* newPair = (KeyValue*)malloc(sizeof(KeyValue));
    newPair->key = strdup(key);
    newPair->value = value;
    newPair->next = NULL;

    if (map->table[index] == NULL) {
        map->table[index] = newPair;
    } else {
        KeyValue* current = map->table[index];
        while (current->next != NULL) {
            if (strcmp(current->key, key) == 0) {
                current->value = value;
                free(newPair->key);
                free(newPair);
                return;
            }
            current = current->next;
        }
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            free(newPair->key);
            free(newPair);
        } else {
            current->next = newPair;
        }
    }
}

/**
 *
 */
void *get(HashMap* map, const char* key) {
    unsigned int index = hash(key);
    KeyValue* current = map->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

/**
 *
 */
void free_hash_map(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue* current = map->table[i];
        while (current != NULL) {
            KeyValue* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map);
}

/**
 *
 */
void print_map(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!map->table[i]) continue;
        Package *value = map->table[i]->value;
        printf("%s\n", map->table[i]->key);
    }
}
