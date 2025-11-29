#pragma once
#include "Lgs_Types.h"

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_SetExpr {
    char* data;
    size_t length;
    size_t capacity;
    Lgs_TypeInfo* baseType;
};