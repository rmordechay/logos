#pragma once
#include "Lgs_types.h"
#include <cstddef>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_DArray {
    char* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    Lgs_rttype baseType;
};

extern "C" Lgs_DArray* Lgs_DArray_init(size_t elementSize, Lgs_rttype baseType);
extern "C" void Lgs_DArray_add(Lgs_DArray* arr, const void* value);
extern "C" size_t Lgs_DArray_len(const Lgs_DArray* arr);
extern "C" void* Lgs_DArray_get(const Lgs_DArray* arr, int64_t index);