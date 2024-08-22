#ifndef LOGOS_HASHMAP_H
#define LOGOS_HASHMAP_H

#define TABLE_SIZE 100

typedef struct KeyValue {
    char* key;
    void *value;
    struct KeyValue* next;
} KeyValue;

typedef struct {
    KeyValue* table[TABLE_SIZE];
} HashMap;

unsigned int hash(const char* key);
HashMap* create_hash_map();
void insert(HashMap* map, const char* key, void *value);
void *get(HashMap* map, const char* key);
void free_hash_map(HashMap* map);
void print_map(HashMap *map);

#endif //LOGOS_HASHMAP_H
