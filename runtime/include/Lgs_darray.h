#pragma once
#include <vector>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_darray {
    size_t elementSize;
    std::vector<char>* data;
};