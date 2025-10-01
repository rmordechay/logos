#include "Lgs_darray.h"
#include "utils/LgsUtils.h"
#include <cstring>

extern "C" void Lgs_DArray_init(Lgs_darray* arr, const size_t elementSize) {
    arr->elementSize = elementSize;
    arr->data = new std::vector<char>();
}

extern "C" void Lgs_DArray_add(const Lgs_darray* arr, const void* value) {
    assert(arr->elementSize <= MAX_ELEMENT_SIZE);
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

extern "C" bool Lgs_DArray_contains(const Lgs_darray* arr, const void* value) {
    if (!arr || !arr->data || arr->data->empty()) return false;
    const size_t len = arr->data->size() / arr->elementSize;
    const char* base = arr->data->data();
    for (size_t i = 0; i < len; ++i) {
        const void* elem = base + i * arr->elementSize;
        if (std::memcmp(elem, value, arr->elementSize) == 0) {
            return true;
        }
    }
    return false;
}
