#include "Lgs_HashMap.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include <cassert>
#include <cstring>
#include <cstdlib>

#define MAP_INITIAL_CAPACITY 10

static void resize(Lgs_HashMap* map);
static Lgs_HashMapEntry* createEntry(const char* key, char* value);

extern "C" void Lgs_Map_init(Lgs_HashMap* map) {
    const auto entries = std::calloc(MAP_INITIAL_CAPACITY, sizeof(Lgs_HashMapEntry));
    map->entries = static_cast<Lgs_HashMapEntry**>(entries);
    map->len = 0;
    map->capacity = MAP_INITIAL_CAPACITY;
}

extern "C" void Lgs_Map_add(Lgs_HashMap* map, const char* key, char* value) {
    if (map->len >= map->capacity) resize(map);
    const auto hashedValue = hashString(key) % map->capacity;
    auto entry = map->entries[hashedValue];
    while (entry) {
        if (strcmp(entry->key, key) == 0) { // Override
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    const auto new_entry = createEntry(key, value);
    map->entries[hashedValue] = new_entry;
    map->len++;
}

extern "C" void* Lgs_Map_get(const Lgs_HashMap* map, const char* key) {
    const auto hashed = hashString(key) % map->capacity;
    auto entry = map->entries[hashed];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return &entry->value;
        entry = entry->next;
    }
    return nullptr;
}

extern "C" void Lgs_Map_delete(Lgs_HashMap* map, const char* key) {
    const auto index = hashString(key) % map->capacity;
    auto entry = map->entries[index];
    Lgs_HashMapEntry* prev = nullptr;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) prev->next = entry->next;
            else map->entries[index] = entry->next;
            free(entry->key);
            free(entry);
            map->len--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

extern "C" void Lgs_Map_free(Lgs_HashMap* map) {
    for (size_t i = 0; i < map->capacity; i++) {
        auto entry = map->entries[i];
        while (entry) {
            const auto next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->entries);
    free(map);
}

extern "C" size_t Lgs_Map_len(const Lgs_HashMap* map) {
    return map ? map->len : 0;
}

extern "C" bool Lgs_Map_isEmpty(const Lgs_HashMap* map) {
    return map ? map->len == 0 : true;
}

extern "C" bool Lgs_Map_isNotEmpty(const Lgs_HashMap* map) {
    return map ? map->len != 0 : false;
}

extern "C" const char* Lgs_Map_getKeyAt(const Lgs_HashMap* map, const size_t index) {
    assert(0);
}

extern "C" void* Lgs_Map_getValueAt(const Lgs_HashMap* map, const size_t index) {
    assert(0);
}

extern "C" Lgs_DArrayExpr* Lgs_Map_keys(const Lgs_HashMap* map, const Lgs_TypeInfo* keyType) {
    assert(0);
}

extern "C" Lgs_DArrayExpr* Lgs_Map_values(const Lgs_HashMap* map, const Lgs_TypeInfo* valueType) {
    assert(0);
}

static void resize(Lgs_HashMap* map) {
    const auto newCap = map->capacity * 2;
    const auto newBuckets = static_cast<Lgs_HashMapEntry**>(calloc(newCap, sizeof(Lgs_HashMapEntry*)));
    for (int i = 0; i < map->capacity; i++) {
        auto entry = map->entries[i];
        while (entry) {
            const auto next = entry->next;
            const auto index = hashString(entry->key) % newCap;
            entry->next = newBuckets[index];
            newBuckets[index] = entry;
            entry = next;
        }
    }
    std::free(map->entries);
    map->entries = newBuckets;
    map->capacity = newCap;
}

static Lgs_HashMapEntry* createEntry(const char* key, char* value) {
    const auto ptr = std::malloc(sizeof(Lgs_HashMapEntry));
    const auto entry = static_cast<Lgs_HashMapEntry*>(ptr);
    entry->key = strdup(key);
    entry->value = value;
    entry->next = nullptr;
    return entry;
}
