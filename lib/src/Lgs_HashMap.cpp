#include "Lgs_HashMap.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include <cassert>
#include <cstring>
#include <cstdlib>

extern "C" void Lgs_Map_init(Lgs_HashMap* map) {
    map->length = 0;
    map->entries = static_cast<Lgs_HashMapEntry*>(std::malloc(LGS_MAP_CAP * sizeof(Lgs_HashMapEntry)));
}

extern "C" void Lgs_Map_add(Lgs_HashMap* map, const Lgs_TypeInfo* type, const char* key, const void* value) {
    if (!map || !key || !value) assert(0);
    const auto index = findSlot(map, key);
    auto& entry = map->entries[index];
    if (!entry.occupied) {
        entry.key = strdup(key);
        entry.value = static_cast<char*>(std::malloc(type->map.valueType->size));
        entry.occupied = true;
        map->length++;
    }
    std::memcpy(entry.value, value, type->map.valueType->size);
}

extern "C" void* Lgs_Map_get(const Lgs_HashMap* map, const char* key) {
    if (!map || !key) assert(0);
    const auto index = findSlot(map, key);
    const auto& entry = map->entries[index];
    if (!entry.occupied) return nullptr;
    return entry.value;
}

extern "C" void Lgs_Map_delete(Lgs_HashMap* map, const char* key) {
    if (!map || !key) assert(0);
    const auto index = findSlot(map, key);
    auto& entry = map->entries[index];
    if (entry.occupied) {
        std::free(entry.key);
        std::free(entry.value);
        entry.occupied = false;
        map->length--;
    }
}

extern "C" size_t Lgs_Map_len(const Lgs_HashMap* map) {
    return map ? map->length : 0;
}

extern "C" bool Lgs_Map_isEmpty(const Lgs_HashMap* map) {
    return map ? map->length == 0 : true;
}

extern "C" bool Lgs_Map_isNotEmpty(const Lgs_HashMap* map) {
    return map ? map->length != 0 : false;
}

extern "C" const char* Lgs_Map_getKeyAt(const Lgs_HashMap* map, const size_t index) {
    if (!map) return nullptr;
    size_t count = 0;
    for (size_t i = 0; i < LGS_MAP_CAP; i++) {
        if (map->entries[i].occupied) {
            if (count == index) return map->entries[i].key;
            count++;
        }
    }
    return nullptr;
}

extern "C" void* Lgs_Map_getValueAt(const Lgs_HashMap* map, const size_t index) {
    if (!map) return nullptr;
    size_t count = 0;
    for (size_t i = 0; i < LGS_MAP_CAP; i++) {
        if (map->entries[i].occupied) {
            if (count == index) return map->entries[i].value;
            count++;
        }
    }
    return nullptr;
}

extern "C" Lgs_DArrayExpr* Lgs_Map_keys(const Lgs_HashMap* map, const Lgs_TypeInfo* keyType) {
    if (!map) return nullptr;
    const auto arr = new Lgs_DArrayExpr();
    Lgs_DArray_init(arr, keyType);
    for (size_t i = 0; i < LGS_MAP_CAP; i++) {
        if (!map->entries[i].occupied) continue;
        const auto keyStr = strdup(map->entries[i].key);
        Lgs_DArray_add(arr, keyType, keyStr);
    }
    return arr;
}

extern "C" Lgs_DArrayExpr* Lgs_Map_values(const Lgs_HashMap* map, const Lgs_TypeInfo* valueType) {
    if (!map) return nullptr;
    const auto arr = new Lgs_DArrayExpr();
    Lgs_DArray_init(arr, valueType);
    for (size_t i = 0; i < LGS_MAP_CAP; i++) {
        if (!map->entries[i].occupied) continue;
        Lgs_DArray_add(arr, valueType, map->entries[i].value);
    }
    return arr;
}

static size_t findSlot(const Lgs_HashMap* map, const char* key) {
    const auto hash = hashString(key);
    size_t index = hash % LGS_MAP_CAP;
    size_t probe = 0;
    while (probe < LGS_MAP_CAP) {
        const auto& entry = map->entries[index];
        if (!entry.occupied || strcmp(entry.key, key) == 0) {
            return index;
        }
        probe++;
        index = (index + 1) % LGS_MAP_CAP;
    }
    return index;
}