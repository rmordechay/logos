#include <cstring>
#include <iostream>
#include <vector>

struct Lgs_Array {
    size_t elementSize;
    std::vector<char>* data;
};

extern "C" void Lgs_DArray_init(Lgs_Array* arr, const size_t elementSize) {
    arr->elementSize = elementSize;
    arr->data = new std::vector<char>();
}

extern "C" void Lgs_DArray_add(const Lgs_Array* arr, const void* value) {
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

extern "C" void Lgs_DArray_addBool(const Lgs_Array* a, const bool v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addShort(const Lgs_Array* a, const int16_t v) {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addInt(const Lgs_Array* a, const int32_t v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addLong(const Lgs_Array* a, const int64_t v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void* Lgs_DArray_get(const Lgs_Array* arr, const size_t index) {
    const auto arrLen = arr->data->size() / arr->elementSize;
    if (index >= arrLen) std::exit(1);
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

extern "C" void Lgs_DArray_free(const Lgs_Array* arr) {
    delete arr->data;
}
