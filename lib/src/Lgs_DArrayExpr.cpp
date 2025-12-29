#include "Lgs_DArrayExpr.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

extern "C" void Lgs_DArray_init(Lgs_DArrayExpr* arr, const Lgs_TypeInfo* dArr) {
    arr->data = static_cast<char*>(std::malloc(arr->capacity * dArr->dArray.baseType->size));
    arr->capacity = 10;
    arr->length = 0;
}

extern "C" void Lgs_DArray_add(Lgs_DArrayExpr* arr, const Lgs_TypeInfo* type, const void* value) {
    assert(arr);
    if (arr->length <= arr->capacity) {
        arr->capacity *= 2;
        arr->data = static_cast<char*>(realloc(arr->data, arr->capacity));
    }
    const auto size = type->dArray.baseType->size;
    const auto dst = arr->data + arr->length * size;
    std::memcpy(dst, value, size);
    arr->length++;
}

extern "C" void Lgs_DArray_put(const Lgs_DArrayExpr* arr, const Lgs_TypeInfo* type, const size_t index, const void* value) {
    if (!arr) return;
    if (index >= arr->length) return;
    std::memcpy(arr->data + index * type->dArray.baseType->size, value, type->dArray.baseType->size);
}

extern "C" void* Lgs_DArray_get(const Lgs_DArrayExpr* arr, const Lgs_TypeInfo* type, const int64_t index) {
    if (index >= arr->length) return nullptr;
    return arr->data + index * type->dArray.baseType->size;
}

extern "C" size_t Lgs_DArray_len(const Lgs_DArrayExpr* arr) {
    return arr->length;
}

extern "C" bool Lgs_DArray_isEmpty(const Lgs_DArrayExpr* arr) {
    return arr->length == 0;
}

extern "C" bool Lgs_DArray_isNotEmpty(const Lgs_DArrayExpr* arr) {
    return arr->length != 0;
}
