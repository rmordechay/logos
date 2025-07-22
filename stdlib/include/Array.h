#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t element_size;
    size_t capacity;
    size_t size;
    void* data;
} Array;

void Array_init(Array* arr, size_t capacity, size_t element_size);
void Array_add(Array* arr, const void* value);
void* Array_get(const Array* arr, size_t index);
size_t Array_len(const Array* arr);
bool Array_isEmpty(const Array* arr);
bool Array_isNotEmpty(const Array* arr);
void Array_free(const Array* arr);

#endif //DYNARRAY_H
