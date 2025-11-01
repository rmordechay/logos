#include "Lgs_DArray.h"
#include "Lgs_Types.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

static void resizeArrIfNeeded(Lgs_DArray* arr);
static bool compare_arrays(const Lgs_DArray* arr1, const Lgs_DArray* arr2);

extern "C" void Lgs_DArray_init(Lgs_DArray* arr, const size_t elementSize, const Lgs_RTType baseType) {
    assert(baseType != RTT_UNKNOWN);
    arr->elementSize = elementSize;
    arr->baseType = baseType;
    arr->capacity = elementSize * 10;
    arr->data = static_cast<char*>(std::malloc(arr->capacity));
    arr->size = 0;
}

extern "C" void Lgs_DArray_reserve(Lgs_DArray* arr, const size_t numElements) {
    assert(arr);
    const auto newCapacity = numElements * arr->elementSize;
    if (newCapacity <= arr->capacity) return;
    arr->data = static_cast<char*>(std::realloc(arr->data, newCapacity));
    arr->capacity = newCapacity;
}

extern "C" void Lgs_DArray_add(Lgs_DArray* arr, const void* value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    std::memcpy(arr->data + arr->size, value, arr->elementSize);
    arr->size += arr->elementSize;
}

extern "C" void Lgs_DArray_addInt(Lgs_DArray* arr, const int32_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<int32_t*>(arr->data + arr->size) = value;
    arr->size += sizeof(int32_t);
}

extern "C" void Lgs_DArray_addLong(Lgs_DArray* arr, const int64_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<int64_t*>(arr->data + arr->size) = value;
    arr->size += sizeof(int64_t);
}

extern "C" void Lgs_DArray_addSize(Lgs_DArray* arr, const size_t value) {
    assert(arr);
    resizeArrIfNeeded(arr);
    *reinterpret_cast<size_t*>(arr->data + arr->size) = value;
    arr->size += sizeof(size_t);
}

extern "C" void Lgs_DArray_put(const Lgs_DArray* arr, const size_t index, const void* value) {
    if (!arr) return;
    const size_t arrLen = arr->size / arr->elementSize;
    if (index >= arrLen) return;
    std::memcpy(arr->data + index * arr->elementSize, value, arr->elementSize);
}

extern "C" void* Lgs_DArray_get(const Lgs_DArray* arr, const int64_t index) {
    if (!arr || arr->size == 0) assert(0);
    const auto arrLen = arr->size / arr->elementSize;
    size_t actualIndex;
    if (index >= 0) {
        actualIndex = index;
    } else {
        // For negative index, cast to positive for comparison
        const auto absIndex = static_cast<size_t>(-index);
        if (absIndex > arrLen) return nullptr;
        actualIndex = arrLen - absIndex;
    }
    if (actualIndex >= arrLen) return nullptr;
    return arr->data + actualIndex * arr->elementSize;
}

extern "C" size_t Lgs_DArray_len(const Lgs_DArray* arr) {
    return arr->size / arr->elementSize;
}

extern "C" bool Lgs_DArray_isEmpty(const Lgs_DArray* arr) {
    return arr->size == 0;
}

extern "C" bool Lgs_DArray_isNotEmpty(const Lgs_DArray* arr) {
    return arr->size != 0;
}

extern "C" bool Lgs_DArray_contains(const Lgs_DArray* arr, const void* value) {
    assert(arr);
    if (arr->size == 0) return false;
    const size_t len = arr->size / arr->elementSize;
    const char* base = arr->data;
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * arr->elementSize;
        bool match = false;
        if (arr->baseType == RTT_DARRAY) {
            const auto nested_elem = *static_cast<const Lgs_DArray* const*>(elem);
            const auto nested_value = *static_cast<const Lgs_DArray* const*>(value);
            match = compare_arrays(nested_elem, nested_value);
        } else if (arr->baseType == RTT_STR) {
            const auto str1 = *static_cast<const char* const*>(elem);
            const auto str2 = *static_cast<const char* const*>(value);
            match = strcmp(str1, str2) == 0;
        } else {
            match = std::memcmp(elem, value, arr->elementSize) == 0;
        }
        if (match) return true;
    }
    return false;
}

static bool compare_arrays(const Lgs_DArray* arr1, const Lgs_DArray* arr2) {
    if (arr1->elementSize != arr2->elementSize) return false;
    if (arr1->baseType != arr2->baseType) return false;
    if (Lgs_DArray_len(arr1) != Lgs_DArray_len(arr2)) return false;

    const size_t len = Lgs_DArray_len(arr1);
    for (size_t i = 0; i < len; ++i) {
        const void* elem1 = Lgs_DArray_get(arr1, i);
        const void* elem2 = Lgs_DArray_get(arr2, i);
        if (arr1->baseType == RTT_DARRAY) {
            const auto nested1 = *static_cast<const Lgs_DArray* const*>(elem1);
            const auto nested2 = *static_cast<const Lgs_DArray* const*>(elem2);
            if (!compare_arrays(nested1, nested2)) return false;
        } else if (arr1->baseType == RTT_STR) {
            const auto str1 = *static_cast<const char* const*>(elem1);
            const auto str2 = *static_cast<const char* const*>(elem2);
            if (strcmp(str1, str2) != 0) return false;
        } else {
            if (std::memcmp(elem1, elem2, arr1->elementSize) != 0) return false;
        }
    }
    return true;
}

static void resizeArrIfNeeded(Lgs_DArray* arr) {
    if (arr->size + arr->elementSize <= arr->capacity) return;
    arr->capacity *= 2;
    arr->data = static_cast<char*>(realloc(arr->data, arr->capacity));
}
