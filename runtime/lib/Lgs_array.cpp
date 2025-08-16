#include <cstring>
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
    auto& vec = *arr->data;
    const auto oldSize = vec.size();
    vec.resize(oldSize + arr->elementSize);
    std::memcpy(vec.data() + oldSize, value, arr->elementSize);
}

extern "C" void Lgs_DArray_addBool(const Lgs_Array* a, const bool v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addShort(const Lgs_Array* a, const int32_t v) {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addInt(const Lgs_Array* a, const bool v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void Lgs_DArray_addLong(const Lgs_Array* a, const bool v)   {
    Lgs_DArray_add(a, &v);
}

extern "C" void* Lgs_DArray_get(const Lgs_Array* arr, const size_t index) {
    auto& vec = *arr->data;
    if (index >= vec.size() / arr->elementSize) std::abort();
    return vec.data() + index * arr->elementSize;
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

extern "C" void Lgs_DArray_free(Lgs_Array* arr) {
    delete arr->data;
    arr->data = nullptr;
}
