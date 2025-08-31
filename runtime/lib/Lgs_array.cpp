#include "configs/LgsErrors.h"
#include "utils/LgsUtils.h"
#include <cstring>
#include <vector>

#define MAX_ELEMENT_SIZE 1024*100

struct Lgs_Array {
    size_t elementSize;
    std::vector<char>* data;
};

extern "C" void Lgs_DArray_init(Lgs_Array* arr, const size_t elementSize) {
    arr->elementSize = elementSize;
    arr->data = new std::vector<char>();
}

extern "C" void Lgs_DArray_add(const Lgs_Array* arr, const void* value) {
    assert(arr->elementSize <= MAX_ELEMENT_SIZE);
    const auto oldSize = arr->data->size();
    arr->data->resize(oldSize + arr->elementSize);
    std::memcpy(arr->data->data() + oldSize, value, arr->elementSize);
}

extern "C" void Lgs_DArray_addMany(const Lgs_Array* arr, const void* values, const size_t count) {
    if (count == 0) return;
    const auto oldSize = arr->data->size();
    const auto bytesToAdd = arr->elementSize * count;
    arr->data->resize(oldSize + bytesToAdd);
    std::memcpy(arr->data->data() + oldSize, values, bytesToAdd);
}

extern "C" void Lgs_DArray_put(const Lgs_Array* arr, const int index, const void* value) {
    if (!arr || !arr->data) return;
    const size_t arrLen = arr->data->size() / arr->elementSize;
    if (index >= arrLen) return;
    std::memcpy(arr->data->data() + index * arr->elementSize, value, arr->elementSize);
}

extern "C" void* Lgs_DArray_get(const Lgs_Array* arr, const size_t index) {
    const auto arrLen = arr->data->size() / arr->elementSize;
    if (index >= arrLen) {
        formatAndLogError(E10080, {std::to_string(index)});
        return nullptr;
    }
    return arr->data->data() + index * arr->elementSize;
}

extern "C" size_t Lgs_DArray_len(const Lgs_Array* arr) {
    return arr->data->size() / arr->elementSize;
}

extern "C" bool Lgs_DArray_isEmpty(const Lgs_Array* arr) {
    return arr->data->empty();
}

extern "C" bool Lgs_DArray_isNotEmpty(const Lgs_Array* arr) {
    return !arr->data->empty();
}

extern "C" bool Lgs_DArray_contains(const Lgs_Array* arr, const void* value) {
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

extern "C" void Lgs_DArray_free(Lgs_Array* arr) {
    delete arr->data;
    std::free(arr);
}