#pragma once
#include "Lgs_types.h"

struct Lgs_hashmap {
    size_t valueSize;
    Lgs_rttype keyType;
    Lgs_rttype valueType;
    std::unordered_map<std::string, std::vector<char>>* data;
};
