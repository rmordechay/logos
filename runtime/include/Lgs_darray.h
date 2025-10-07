#pragma once
#include "Lgs_types.h"

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_darray {
    char* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    Lgs_rttype baseType;
};

extern "C" void Lgs_DArray_init(Lgs_darray* arr, size_t elementSize, Lgs_rttype baseType);
extern "C" void Lgs_DArray_add(Lgs_darray* arr, const void* value);
extern "C" size_t Lgs_DArray_len(const Lgs_darray* arr);
extern "C" void* Lgs_DArray_get(const Lgs_darray* arr, int64_t index);