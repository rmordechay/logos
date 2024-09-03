#ifndef LOGOS_HASHMAP_H
#define LOGOS_HASHMAP_H

#define TABLE_SIZE 20

typedef struct KeyValue {
    char* key;
    union {
        void *value;
        struct Package *package;
        struct AppFile *file;
        struct Symbol *symbol;
    };
    struct KeyValue* next;
} KeyValue;

typedef struct HashMap {
    KeyValue* table[TABLE_SIZE];
} HashMap;

unsigned int hash(const char* key);
HashMap* create_hash_map();
void put_in_map(HashMap* map, const char* key, void *value);
KeyValue *get_from_map(HashMap* map, const char* key);
void free_hash_map(HashMap* map);
void print_map(HashMap *map);

#endif //LOGOS_HASHMAP_H
