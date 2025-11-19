#pragma once
#include "Lgs_Types.h"

struct Lgs_DArray {
    char* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    Lgs_TypeKind baseType;
};

extern "C" void Lgs_DArray_init(Lgs_DArray* arr, size_t elementSize, Lgs_TypeKind baseType);
extern "C" void Lgs_DArray_add(Lgs_DArray* arr, const void* value);
extern "C" size_t Lgs_DArray_len(const Lgs_DArray* arr);
extern "C" void* Lgs_DArray_get(const Lgs_DArray* arr, int64_t index);
