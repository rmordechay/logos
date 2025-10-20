#include "Lgs_hashmap.h"
#include "Lgs_darray.h"
#include "types/iterables/LgsMap.h"
#include "utils/LgsUtils.h"

extern "C" size_t Lgs_hash(const char* s) {
    return hashStr(s);
}

extern "C" void Lgs_map_init(Lgs_hashmap* map, const size_t valueSize, const Lgs_rttype keyType, const Lgs_rttype valueType) {
    assert(keyType != RTT_UNKNOWN && valueType != RTT_UNKNOWN);
    if (!map || valueSize == 0 || valueSize > 4096) std::exit(1);
    map->valueSize = valueSize;
    map->keyType = keyType;
    map->valueType = valueType;
    map->data = new std::unordered_map<std::string, std::vector<char>>();
}

extern "C" void Lgs_map_add(const Lgs_hashmap* map, const char* key, const void* value) {
    if (!map || !key || !value) assert(0);
    if (std::strlen(key) > 1024) assert(0);
    auto& vec = (*map->data)[key];
    vec.resize(map->valueSize);
    std::memcpy(vec.data(), value, map->valueSize);
}

extern "C" void* Lgs_map_get(const Lgs_hashmap* map, const char* key) {
    if (!map || !key || !map->data) assert(0);
    const auto v = map->data->find(key);
    if (v == map->data->end()) {
        exitWithError(E10067, {key});
        return nullptr;
    }
    return v->second.data();
}

extern "C" void Lgs_map_delete(const Lgs_hashmap* map, const char* key) {
    if (!map || !key) assert(0);
    map->data->erase(key);
}

extern "C" size_t Lgs_map_len(const Lgs_hashmap* map) {
    return map ? map->data->size() : 0;
}

extern "C" bool Lgs_map_isEmpty(const Lgs_hashmap* map) {
    return map ? map->data->empty() : true;
}

extern "C" bool Lgs_map_isNotEmpty(const Lgs_hashmap* map) {
    return map ? !map->data->empty() : false;
}

extern "C" const char* Lgs_map_getKeyAt(const Lgs_hashmap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->first.c_str();
}

extern "C" void* Lgs_map_getValueAt(const Lgs_hashmap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->second.data();
}

extern "C" Lgs_darray* Lgs_map_keys(const Lgs_hashmap* map) {
    if (!map) return nullptr;
    const auto keys = new Lgs_darray();
    Lgs_darray_init(keys, sizeof(char*), map->keyType);
    for (const auto& [k, v] : *map->data) {
        const auto keyStr = strdup(k.c_str());
        Lgs_darray_add(keys, keyStr);
    }
    return keys;
}

extern "C" Lgs_darray* Lgs_map_values(const Lgs_hashmap* map) {
    if (!map) return nullptr;
    const auto values = new Lgs_darray;
    Lgs_darray_init(values, map->valueSize, map->valueType);
    for (const auto& [k, v] : *map->data) {
        Lgs_darray_add(values, v.data());
    }
    return values;
}
