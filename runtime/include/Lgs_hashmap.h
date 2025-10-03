#pragma once
#include "Lgs_types.h"

struct Lgs_hashmap {
    size_t valueSize;
    Lgs_RTType keyType;
    Lgs_RTType valueType;
    std::unordered_map<std::string, std::vector<char>>* data;
};
