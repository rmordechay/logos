#pragma once
#include <vector>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_Array {
    size_t elementSize;
    std::vector<char>* data;
};

extern "C" void Lgs_DArray_free(Lgs_Array* arr);