#pragma once
#include "Lgs_Types.h"
#include <cstddef>

#define LGS_DARRAY_MAX_LENGTH 100000

struct Lgs_DArrayExpr {
    char* data;
    size_t length;
    size_t capacity;
    Lgs_TypeInfo* baseType;
};

extern "C" void Lgs_DArray_init(Lgs_DArrayExpr* arr, Lgs_TypeInfo* baseType);
extern "C" void Lgs_DArray_add(Lgs_DArrayExpr* arr, const void* value);
extern "C" size_t Lgs_DArray_len(const Lgs_DArrayExpr* arr);
extern "C" void* Lgs_DArray_get(const Lgs_DArrayExpr* arr, int64_t index);
