#include "types/LgsMap.h"
#include "utils/LgsErrHandler.h"
#include "utils/LgsUtils.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>

struct Lgs_Map {
    size_t valueSize;
    LgsErrHandler errHandler;
    std::unordered_map<std::string, std::vector<char>>* data;
};

extern "C" void Lgs_Map_init(Lgs_Map* map, const size_t valueSize) {
    if (!map || valueSize == 0 || valueSize > 4096) std::exit(1);
    map->valueSize = valueSize;
    map->data = new std::unordered_map<std::string, std::vector<char>>();
}

extern "C" void Lgs_Map_add(const Lgs_Map* map, const char* key, const void* value) {
    if (!map || !key || !value) std::exit(1);
    if (std::strlen(key) > 1024) std::exit(1);
    auto& vec = (*map->data)[key];
    vec.resize(map->valueSize);
    std::memcpy(vec.data(), value, map->valueSize);
}

extern "C" void* Lgs_Map_get(const Lgs_Map* map, const char* key) {
    if (!map || !key) std::exit(1);
    const auto it = map->data->find(key);
    if (it == map->data->end()) {
        std::string msg;
        formatErrorMsg(E10067, {key, LgsMap::name}, msg);
        std::cout << msg << std::endl;
        return nullptr;
    }
    return it->second.data();
}

extern "C" void Lgs_Map_delete(const Lgs_Map* map, const char* key) {
    if (!map || !key) std::exit(1);
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

extern "C" void Lgs_Map_free(const Lgs_Map* map) {
    if (!map) return;
    delete map->data;
}
