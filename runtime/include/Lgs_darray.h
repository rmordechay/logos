#pragma once
#include "Lgs_types.h"
#include <vector>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_darray {
    size_t elementSize;
    Lgs_RTType baseType;
    std::vector<char>* data;
};

extern "C" void Lgs_DArray_init(Lgs_darray* arr, size_t elementSize, Lgs_RTType baseType);
extern "C" void Lgs_DArray_add(const Lgs_darray* arr, const void* value);
extern "C" size_t Lgs_DArray_len(const Lgs_darray* arr);
extern "C" void* Lgs_DArray_get(const Lgs_darray* arr, int64_t index);