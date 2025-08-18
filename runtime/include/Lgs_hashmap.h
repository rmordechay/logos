#pragma once
#include "utils/LgsErrHandler.h"

struct Lgs_Map {
    size_t valueSize;
    LgsErrHandler errHandler;
    std::unordered_map<std::string, std::vector<char>>* data;
};