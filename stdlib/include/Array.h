#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <stddef.h>
#include <_types/_uint32_t.h>

typedef struct {
    size_t element_size;
    uint32_t capacity;
    uint32_t size;
    void* data;
} Array;

Array* Array_new(uint32_t capacity, size_t element_size);
void Array_add(Array* arr, const void* value);
void* Array_get(const Array* arr, uint32_t index);
size_t Array_len(const Array* arr);
void Array_fre(Array* arr);

#endif //DYNARRAY_H
