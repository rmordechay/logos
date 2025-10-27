#pragma once
#include "Lgs_types.h"

#include <unordered_map>
#include <vector>

struct Lgs_Map {
    size_t valueSize;
    Lgs_rttype keyType;
    Lgs_rttype valueType;
    std::unordered_map<std::string, std::vector<char>>* data;
};
