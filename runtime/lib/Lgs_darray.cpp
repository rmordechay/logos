#include "Lgs_darray.h"

#include "Lgs_types.h"
#include "utils/LgsUtils.h"
#include <cstring>

extern "C" void Lgs_DArray_init(Lgs_darray* arr, const size_t elementSize, const Lgs_RTType baseType) {
    assert(baseType != RTT_UNKNOWN);
    arr->elementSize = elementSize;
    arr->baseType = baseType;
    arr->data = new std::vector<char>();
}

extern "C" void Lgs_DArray_add(const Lgs_darray* arr, const void* value) {
    assert(arr);
    const auto oldSize = arr->data->size();
    arr->data->resize(oldSize + arr->elementSize);
    std::memcpy(arr->data->data() + oldSize, value, arr->elementSize);
}

extern "C" void Lgs_DArray_put(const Lgs_darray* arr, const int index, const void* value) {
    if (!arr || !arr->data) return;
    const size_t arrLen = arr->data->size() / arr->elementSize;
    if (index >= arrLen) return;
    std::memcpy(arr->data->data() + index * arr->elementSize, value, arr->elementSize);
}

extern "C" void* Lgs_DArray_get(const Lgs_darray* arr, const int64_t index) {
    if (!arr || arr->data->empty()) assert(0);
    const auto arrLen = arr->data->size() / arr->elementSize;
    size_t actualIndex;
    if (index >= 0) {
        actualIndex = index;
    } else {
        if (-index > arrLen) {
            return nullptr;
        }
        actualIndex = arrLen + index;
    }
    if (actualIndex >= arrLen) {
        return nullptr;
    }
    return arr->data->data() + actualIndex * arr->elementSize;
}

extern "C" size_t Lgs_DArray_len(const Lgs_darray* arr) {
    return arr->data->size() / arr->elementSize;
}

extern "C" bool Lgs_DArray_isEmpty(const Lgs_darray* arr) {
    return arr->data->empty();
}

extern "C" bool Lgs_DArray_isNotEmpty(const Lgs_darray* arr) {
    return !arr->data->empty();
}

bool compare_arrays(const Lgs_darray* arr1, const Lgs_darray* arr2) {
    if (arr1->elementSize != arr2->elementSize) return false;
    if (arr1->baseType != arr2->baseType) return false;
    if (Lgs_DArray_len(arr1) != Lgs_DArray_len(arr2)) return false;
    const size_t len = Lgs_DArray_len(arr1);
    for (size_t i = 0; i < len; ++i) {
        const void* elem1 = Lgs_DArray_get(arr1, i);
        const void* elem2 = Lgs_DArray_get(arr2, i);
        if (arr1->baseType == RTT_DARRAY) {
            const auto nested1 = static_cast<const Lgs_darray*>(elem1);
            const auto nested2 = static_cast<const Lgs_darray*>(elem2);
            if (!compare_arrays(nested1, nested2)) return false;
        } else if (arr1->baseType == RTT_STR) {
            const auto str1 = static_cast<const char*>(elem1);
            const auto str2 = static_cast<const char*>(elem2);
            if (strcmp(str1, str2) != 0) return false;
        } else {
            if (std::memcmp(elem1, elem2, arr1->elementSize) != 0) return false;
        }
    }
    return true;
}

extern "C" bool Lgs_DArray_contains(const Lgs_darray* arr, const void* value) {
    assert(arr);
    if (arr->data->empty()) return false;
    const size_t len = arr->data->size() / arr->elementSize;
    const char* base = arr->data->data();
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * arr->elementSize;
        bool match = false;
        if (arr->baseType == RTT_DARRAY) {
            const auto nested_elem = static_cast<const Lgs_darray*>(elem);
            const auto nested_value = static_cast<const Lgs_darray*>(value);
            match = compare_arrays(nested_elem, nested_value);
        } else if (arr->baseType == RTT_STR) {
            const auto str1 = static_cast<const char*>(elem);
            const auto str2 = static_cast<const char*>(value);
            match = strcmp(str1, str2) == 0;
        } else {
            match = std::memcmp(elem, value, arr->elementSize) == 0;
        }
        if (match) return true;
    }
    return false;
}
