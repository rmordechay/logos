#pragma once
#include <vector>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_darray {
    size_t elementSize;
    std::vector<char>* data;
};

extern "C" void Lgs_DArray_init(Lgs_darray* arr, size_t elementSize);
extern "C" void Lgs_DArray_add(const Lgs_darray* arr, const void* value);