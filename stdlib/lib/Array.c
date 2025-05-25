#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t element_size;
    uint32_t capacity;
    uint32_t size;
    void* data;
} Array;

Array* Array_new(const uint32_t capacity, const size_t element_size) {
    Array* arr = malloc(sizeof(Array));
    if (!arr) return NULL;
    arr->capacity = capacity;
    arr->size = 0;
    arr->element_size = element_size;
    arr->data = malloc(capacity * element_size);
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    return arr;
}

void resize(Array* arr) {
    arr->capacity *= 2;
    void* new_data = realloc(arr->data, arr->capacity * arr->element_size);
    if (!new_data) return;
    arr->data = new_data;
}

void Array_add(Array* arr, const void* value) {
    if (arr->size == arr->capacity) {
        resize(arr);
    }
    void* target = (char*)arr->data + arr->size * arr->element_size;
    memcpy(target, value, arr->element_size);
    arr->size++;
}

void* Array_get(const Array* arr, const uint32_t index) {
    if (index >= arr->size) return NULL;
    return arr->data + index * arr->element_size;
}

size_t Array_len(const Array* arr) {
    return arr->size;
}

void Array_free(Array* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}
