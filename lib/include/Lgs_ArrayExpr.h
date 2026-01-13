#pragma once
#include "Lgs_Types.h"

#define LGS_DARRAY_MAX_LENGTH 100000

struct Lgs_SArrayExpr {
    void* data;
    size_t length;
};

struct Lgs_ArrayExpr {
    char* data;
    size_t length;
    size_t capacity;
};

struct Lgs_HashMap {
    void** entries;
    size_t len;
    size_t capacity;
};