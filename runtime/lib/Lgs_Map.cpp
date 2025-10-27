#include "Lgs_Map.h"
#include "Lgs_DArray.h"
#include "types/iterables/LgsMap.h"
#include "utils/LgsUtils.h"

extern "C" size_t Lgs_hash(const char* s) {
    return hashStr(s);
}

extern "C" void Lgs_Map_init(Lgs_Map* map, const size_t valueSize, const Lgs_RTType keyType, const Lgs_RTType valueType) {
    assert(keyType != RTT_UNKNOWN && valueType != RTT_UNKNOWN);
    if (!map || valueSize == 0 || valueSize > 4096) std::exit(1);
    map->valueSize = valueSize;
    map->keyType = keyType;
    map->valueType = valueType;
    map->data = new std::unordered_map<std::string, std::vector<char>>();
}

extern "C" void Lgs_Map_add(const Lgs_Map* map, const char* key, const void* value) {
    if (!map || !key || !value) assert(0);
    if (std::strlen(key) > 1024) assert(0);
    auto& vec = (*map->data)[key];
    vec.resize(map->valueSize);
    std::memcpy(vec.data(), value, map->valueSize);
}

extern "C" void* Lgs_Map_get(const Lgs_Map* map, const char* key) {
    if (!map || !key || !map->data) assert(0);
    const auto v = map->data->find(key);
    if (v == map->data->end()) {
        exitWithError(E10067, {key});
        return nullptr;
    }
    return v->second.data();
}

extern "C" void Lgs_Map_delete(const Lgs_Map* map, const char* key) {
    if (!map || !key) assert(0);
    map->data->erase(key);
}

extern "C" size_t Lgs_Map_len(const Lgs_Map* map) {
    return map ? map->data->size() : 0;
}

extern "C" bool Lgs_Map_isEmpty(const Lgs_Map* map) {
    return map ? map->data->empty() : true;
}

extern "C" bool Lgs_Map_isNotEmpty(const Lgs_Map* map) {
    return map ? !map->data->empty() : false;
}

extern "C" const char* Lgs_Map_getKeyAt(const Lgs_Map* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->first.c_str();
}

extern "C" void* Lgs_Map_getValueAt(const Lgs_Map* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->second.data();
}

extern "C" Lgs_DArray* Lgs_Map_keys(const Lgs_Map* map) {
    if (!map) return nullptr;
    const auto keys = Lgs_DArray_init(sizeof(char*), map->keyType);
    for (const auto& [k, v] : *map->data) {
        const auto keyStr = strdup(k.c_str());
        Lgs_DArray_add(keys, keyStr);
    }
    return keys;
}

extern "C" Lgs_DArray* Lgs_Map_values(const Lgs_Map* map) {
    if (!map) return nullptr;
    const auto values = Lgs_DArray_init(map->valueSize, map->valueType);
    for (const auto& [k, v] : *map->data) {
        Lgs_DArray_add(values, v.data());
    }
    return values;
}
