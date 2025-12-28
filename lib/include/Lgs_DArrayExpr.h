#pragma once
#include "Lgs_Types.h"

#define LGS_DARRAY_MAX_LENGTH 100000

struct Lgs_SArrayExpr {
    void* data;
    size_t length;
};

struct Lgs_DArrayExpr {
    char* data;
    size_t length;
    size_t capacity;
};

extern "C" void* Lgs_DArray_get(const Lgs_DArrayExpr* arr, const Lgs_TypeInfo* type, int64_t index);
