#include "Array.h"
#include "Iterator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void resize(Array* arr, const size_t new_size) {
    if (arr->capacity >= new_size) return;
    size_t new_capacity = arr->capacity ? arr->capacity : 1;
    while (new_capacity < new_size) {
        new_capacity *= 2;
    }
    void* new_data = realloc(arr->data, new_capacity * arr->element_size);
    if (!new_data) return;
    arr->data = new_data;
    arr->capacity = new_capacity;
}

void Array_init(Array* arr, const size_t capacity, const size_t element_size) {
    arr->capacity = capacity;
    arr->size = 0;
    arr->element_size = element_size;
    arr->data = malloc(capacity * element_size);
    if (!arr->data) exit(1);
}

void Array_add(Array* arr, const size_t values_count, const void* values) {
    const size_t required = arr->size + values_count;
    resize(arr, required);
    void* target = (char*)arr->data + arr->size * arr->element_size;
    memcpy(target, values, values_count * arr->element_size);
    arr->size += values_count;
}

void* Array_get(const Array* arr, const size_t index) {
    if (index >= arr->size) return NULL;
    return arr->data + index * arr->element_size;
}

size_t Array_len(const Array* arr) {
    return arr->size;
}

bool Array_isEmpty(const Array* arr) {
    return arr->size == 0;
}

bool Array_isNotEmpty(const Array* arr) {
    return arr->size != 0;
}

void Array_free(const Array* arr) {
    free(arr->data);
}

bool ArrayIter_hasNext(Iterator* iter) {
    const Array* arr = iter->container;
    return iter->current >= arr->size;
}

void* ArrayIter_next(Iterator* iter) {
    const Array* arr = iter->container;
    if (iter->current >= arr->size) return NULL;
    void* elem = (char*)arr->data + iter->current * arr->element_size;
    iter->current++;
    return elem;
}

Iterator Iterator_fromArray(Array* arr) {
    Iterator iter;
    iter.container = (void*)arr;
    iter.current = 0;
    iter.entry = NULL;
    iter.hasNext = ArrayIter_hasNext;
    iter.next = ArrayIter_next;
    iter.reset = Iter_reset;
    return iter;
}
