#pragma once
#include "Lgs_types.h"
#include <cstddef>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_Set {
    char* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    Lgs_rttype baseType;
};