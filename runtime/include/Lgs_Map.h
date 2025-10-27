#pragma once
#include "Lgs_Types.h"
#include <unordered_map>
#include <vector>
#include <string>

struct Lgs_Map {
    size_t valueSize;
    Lgs_RTType keyType;
    Lgs_RTType valueType;
    std::unordered_map<std::string, std::vector<char>>* data;
};
