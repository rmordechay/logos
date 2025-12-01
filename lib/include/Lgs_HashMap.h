#pragma once
#include "Lgs_Types.h"
#include <unordered_map>
#include <vector>
#include <string>

struct Lgs_HashMap {
    Lgs_Map mapType;
    size_t valueSize;
    std::unordered_map<std::string, std::vector<char>>* data;
};
