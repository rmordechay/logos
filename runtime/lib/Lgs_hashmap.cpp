#include "Lgs_hashmap.h"

#include "Lgs_darray.h"
#include "types/iterables/LgsMap.h"
#include "utils/LgsUtils.h"

extern "C" void Lgs_Map_init(Lgs_hashmap* map, const size_t valueSize) {
    if (!map || valueSize == 0 || valueSize > 4096) std::exit(1);
    map->valueSize = valueSize;
    map->data = new std::unordered_map<std::string, std::vector<char>>();
}

extern "C" void Lgs_Map_add(const Lgs_hashmap* map, const char* key, const void* value) {
    if (!map || !key || !value) assert(0);
    if (std::strlen(key) > 1024) assert(0);
    auto& vec = (*map->data)[key];
    vec.resize(map->valueSize);
    std::memcpy(vec.data(), value, map->valueSize);
}

extern "C" void* Lgs_Map_get(const Lgs_hashmap* map, const char* key) {
    if (!map || !key) assert(0);
    const auto it = map->data->find(key);
    if (it == map->data->end()) {
        formatAndLogError(E10067, {key});
        return nullptr;
    }
    return it->second.data();
}

extern "C" void Lgs_Map_delete(const Lgs_hashmap* map, const char* key) {
    if (!map || !key) assert(0);
    map->data->erase(key);
}

extern "C" size_t Lgs_Map_len(const Lgs_hashmap* map) {
    return map ? map->data->size() : 0;
}

extern "C" bool Lgs_Map_isEmpty(const Lgs_hashmap* map) {
    return map ? map->data->empty() : true;
}

extern "C" bool Lgs_Map_isNotEmpty(const Lgs_hashmap* map) {
    return map ? !map->data->empty() : false;
}

extern "C" const char* Lgs_Map_getKeyAt(const Lgs_hashmap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->first.c_str();
}

extern "C" void* Lgs_Map_getValueAt(const Lgs_hashmap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->second.data();
}

extern "C" Lgs_darray* Lgs_Map_keys(const Lgs_hashmap* map) {
    if (!map) return nullptr;
    const auto keys = new Lgs_darray();
    Lgs_DArray_init(keys, sizeof(char*));
    for (const auto& [k, v] : *map->data) {
        const auto keyStr = strdup(k.c_str());
        Lgs_DArray_add(keys, &keyStr);
    }
    return keys;
}

extern "C" Lgs_darray* Lgs_Map_values(const Lgs_hashmap* map) {
    if (!map) return nullptr;
    const auto values = new Lgs_darray;
    Lgs_DArray_init(values, map->valueSize);
    for (const auto& [k, v] : *map->data) {
        Lgs_DArray_add(values, v.data());
    }
    return values;
}
