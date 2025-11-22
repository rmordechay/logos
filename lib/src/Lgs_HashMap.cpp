#include "Lgs_HashMap.h"
#include <cstring>
#include "Lgs_DArrayExpr.h"
#include "errors/LgsErrors.h"
#include <cassert>
#include <string>
#include <iostream>

extern "C" size_t Lgs_hash(const char* s) {
    return std::hash<std::string_view>{}(s);
}

extern "C" void Lgs_HashMap_init(Lgs_HashMap* map, const size_t valueSize, const Lgs_TypeKind keyType, const Lgs_TypeKind valueType) {
    assert(keyType != RTT_UNKNOWN && valueType != RTT_UNKNOWN);
    if (!map || valueSize == 0 || valueSize > 4096) std::exit(1);
    map->valueSize = valueSize;
    map->keyType = keyType;
    map->valueType = valueType;
    map->data = new std::unordered_map<std::string, std::vector<char>>();
}

extern "C" void Lgs_HashMap_add(const Lgs_HashMap* map, const char* key, const void* value) {
    if (!map || !key || !value) assert(0);
    if (std::strlen(key) > 1024) assert(0);
    auto& vec = (*map->data)[key];
    vec.resize(map->valueSize);
    std::memcpy(vec.data(), value, map->valueSize);
}

extern "C" void* Lgs_HashMap_get(const Lgs_HashMap* map, const char* key) {
    if (!map || !key || !map->data) assert(0);
    const auto v = map->data->find(key);
    if (v == map->data->end()) {
        // exitWithError(E10067, {key});
        return nullptr;
    }
    return v->second.data();
}

extern "C" void Lgs_HashMap_delete(const Lgs_HashMap* map, const char* key) {
    if (!map || !key) assert(0);
    map->data->erase(key);
}

extern "C" size_t Lgs_HashMap_len(const Lgs_HashMap* map) {
    return map ? map->data->size() : 0;
}

extern "C" bool Lgs_HashMap_isEmpty(const Lgs_HashMap* map) {
    return map ? map->data->empty() : true;
}

extern "C" bool Lgs_HashMap_isNotEmpty(const Lgs_HashMap* map) {
    return map ? !map->data->empty() : false;
}

extern "C" const char* Lgs_HashMap_getKeyAt(const Lgs_HashMap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->first.c_str();
}

extern "C" void* Lgs_HashMap_getValueAt(const Lgs_HashMap* map, const size_t index) {
    if (!map || index >= map->data->size()) return nullptr;
    auto it = map->data->begin();
    std::advance(it, index);
    return it->second.data();
}

extern "C" Lgs_DArrayExpr* Lgs_HashMap_keys(const Lgs_HashMap* map) {
    if (!map) return nullptr;
    const auto arr = new Lgs_DArrayExpr();
    Lgs_DArrayExpr_init(arr, sizeof(char*), map->keyType);
    for (const auto& [k, v] : *map->data) {
        const auto keyStr = strdup(k.c_str());
        Lgs_DArrayExpr_add(arr, keyStr);
    }
    return arr;
}

extern "C" Lgs_DArrayExpr* Lgs_HashMap_values(const Lgs_HashMap* map) {
    if (!map) return nullptr;
    const auto arr = new Lgs_DArrayExpr();
    Lgs_DArrayExpr_init(arr, map->valueSize, map->valueType);
    for (const auto& [k, v] : *map->data) {
        Lgs_DArrayExpr_add(arr, v.data());
    }
    return arr;
}
