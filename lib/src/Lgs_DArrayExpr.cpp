#include "Lgs_DArrayExpr.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

static void resizeArrIfNeeded(Lgs_DArrayExpr* arr);
static bool compare_arrays(const Lgs_DArrayExpr* arr1, const Lgs_DArrayExpr* arr2);

extern "C" void Lgs_DArray_init(Lgs_DArrayExpr* arr, Lgs_TypeInfo* baseType) {
    assert(baseType->kind != RTT_UNKNOWN);
    arr->baseType = baseType;
    arr->capacity = 10;
    arr->data = static_cast<char*>(std::malloc(arr->capacity * baseType->size));
    arr->length = 0;
}

extern "C" void Lgs_DArray_reserve(Lgs_DArrayExpr* arr, const size_t numElements) {
    assert(arr);
    if (numElements <= arr->capacity) return;
    arr->data = static_cast<char*>(std::realloc(arr->data, numElements * arr->baseType->size));
    arr->capacity = numElements;
}

extern "C" void Lgs_DArray_add(Lgs_DArrayExpr* arr, const void* value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    std::memcpy(arr->data + arr->length * arr->baseType->size, value, arr->baseType->size);
    arr->length += 1;
}

extern "C" void Lgs_DArray_addInt(Lgs_DArrayExpr* arr, const int32_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<int32_t*>(arr->data + arr->length * arr->baseType->size) = value;
    arr->length += 1;
}

extern "C" void Lgs_DArray_addLong(Lgs_DArrayExpr* arr, const int64_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<int64_t*>(arr->data + arr->length * arr->baseType->size) = value;
    arr->length += 1;
}

extern "C" void Lgs_DArray_addSize(Lgs_DArrayExpr* arr, const size_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<size_t*>(arr->data + arr->length * arr->baseType->size) = value;
    arr->length += 1;
}

extern "C" void Lgs_DArray_put(const Lgs_DArrayExpr* arr, const size_t index, const void* value) {
    if (!arr) return;
    if (index >= arr->length) return;
    std::memcpy(arr->data + index * arr->baseType->size, value, arr->baseType->size);
}

extern "C" void* Lgs_DArray_get(const Lgs_DArrayExpr* arr, const int64_t index) {
    if (index >= arr->length) return nullptr;
    size_t actualIndex;
    if (index >= 0) {
        actualIndex = index;
    } else {
        const auto absIndex = static_cast<size_t>(-index);
        if (absIndex > arr->length) return nullptr;
        actualIndex = arr->length - absIndex;
    }
    if (actualIndex >= arr->length) return nullptr;
    return arr->data + actualIndex * arr->baseType->size;
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

extern "C" bool Lgs_DArray_contains(const Lgs_DArrayExpr* arr, const void* value) {
    assert(arr);
    if (arr->length == 0) return false;
    const size_t len = arr->length / arr->baseType->size;
    const char* base = arr->data;
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * arr->baseType->size;
        bool match = false;
        if (arr->baseType->kind == RTT_DARRAY) {
            const auto nested_elem = *static_cast<const Lgs_DArrayExpr* const*>(elem);
            const auto nested_value = *static_cast<const Lgs_DArrayExpr* const*>(value);
            match = compare_arrays(nested_elem, nested_value);
        } else if (arr->baseType->kind == RTT_STR) {
            const auto str1 = *static_cast<const char* const*>(elem);
            const auto str2 = *static_cast<const char* const*>(value);
            match = strcmp(str1, str2) == 0;
        } else {
            match = std::memcmp(elem, value, arr->baseType->size) == 0;
        }
        if (match) return true;
    }
    return false;
}

static bool compare_arrays(const Lgs_DArrayExpr* arr1, const Lgs_DArrayExpr* arr2) {
    if (arr1->baseType->size != arr2->baseType->size) return false;
    if (arr1->baseType != arr2->baseType) return false;
    if (Lgs_DArray_len(arr1) != Lgs_DArray_len(arr2)) return false;

    const size_t len = Lgs_DArray_len(arr1);
    for (size_t i = 0; i < len; ++i) {
        const void* elem1 = Lgs_DArray_get(arr1, i);
        const void* elem2 = Lgs_DArray_get(arr2, i);
        if (arr1->baseType->kind == RTT_DARRAY) {
            const auto nested1 = *static_cast<const Lgs_DArrayExpr* const*>(elem1);
            const auto nested2 = *static_cast<const Lgs_DArrayExpr* const*>(elem2);
            if (!compare_arrays(nested1, nested2)) return false;
        } else if (arr1->baseType->kind == RTT_STR) {
            const auto str1 = *static_cast<const char* const*>(elem1);
            const auto str2 = *static_cast<const char* const*>(elem2);
            if (strcmp(str1, str2) != 0) return false;
        } else {
            if (std::memcmp(elem1, elem2, arr1->baseType->size) != 0) return false;
        }
    }
    return true;
}

static void resizeArrIfNeeded(Lgs_DArrayExpr* arr) {
    if (arr->length <= arr->capacity) return;
    arr->capacity *= 2;
    arr->data = static_cast<char*>(realloc(arr->data, arr->capacity));
}
