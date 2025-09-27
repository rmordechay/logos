#pragma once

struct Lgs_hashmap {
    size_t valueSize;
    std::unordered_map<std::string, std::vector<char>>* data;
};