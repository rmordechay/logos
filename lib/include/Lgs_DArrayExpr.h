#pragma once
#include "Lgs_Types.h"
#include <cstddef>

struct Lgs_DArrayExpr {
    char* data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    Lgs_TypeKind baseType;
};

extern "C" void Lgs_DArrayExpr_init(Lgs_DArrayExpr* arr, size_t elementSize, Lgs_TypeKind baseType);
extern "C" void Lgs_DArrayExpr_add(Lgs_DArrayExpr* arr, const void* value);
extern "C" size_t Lgs_DArrayExpr_len(const Lgs_DArrayExpr* arr);
extern "C" void* Lgs_DArrayExpr_get(const Lgs_DArrayExpr* arr, int64_t index);
