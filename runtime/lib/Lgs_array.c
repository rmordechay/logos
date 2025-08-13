#include "Lgs_iterator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t element_size;
    size_t capacity;
    size_t size;
    void* data;
} Lgs_Array;

void Lgs_Array_init(Lgs_Array* arr, const size_t capacity, const size_t element_size) {
    arr->capacity = capacity;
    arr->size = 0;
    arr->element_size = element_size;
    arr->data = malloc(capacity * element_size);
    if (!arr->data) exit(1);
}

static void resize(Lgs_Array* arr) {
    arr->capacity *= 2;
    void* new_data = realloc(arr->data, arr->capacity * arr->element_size);
    if (!new_data) return;
    arr->data = new_data;
}

void Lgs_Array_add(Lgs_Array* arr, const void* value) {
    if (arr->size == arr->capacity) resize(arr);
    void* target = (char*)arr->data + arr->size * arr->element_size;
    memcpy(target, value, arr->element_size);
    arr->size++;
}

void Lgs_Array_addBool(Lgs_Array* arr, const bool value) {
    Lgs_Array_add(arr, &value);
}

void Lgs_Array_addByte(Lgs_Array* arr, const int8_t value) {
    Lgs_Array_add(arr, &value);
}

void Lgs_Array_addShort(Lgs_Array* arr, const int16_t value) {
    Lgs_Array_add(arr, &value);
}

void Lgs_Array_addInt(Lgs_Array* arr, const int32_t value) {
    Lgs_Array_add(arr, &value);
}

void Lgs_Array_addLong(Lgs_Array* arr, const int64_t value) {
    Lgs_Array_add(arr, &value);
}

void* Lgs_Array_get(const Lgs_Array* arr, const size_t index) {
    if (index >= arr->size) return NULL;
    return arr->data + index * arr->element_size;
}

size_t Lgs_Array_len(const Lgs_Array* arr) {
    return arr->size;
}

bool Lgs_Array_isEmpty(const Lgs_Array* arr) {
    return arr->size == 0;
}

bool Lgs_Array_isNotEmpty(const Lgs_Array* arr) {
    return arr->size != 0;
}

void Lgs_Array_free(const Lgs_Array* arr) {
    free(arr->data);
}

bool Lgs_ArrayIter_hasNext(Lgs_Iterator* iter) {
    const Lgs_Array* arr = iter->container;
    return iter->current >= arr->size;
}

void* Lgs_ArrayIter_next(Lgs_Iterator* iter) {
    const Lgs_Array* arr = iter->container;
    if (iter->current >= arr->size) return NULL;
    void* elem = (char*)arr->data + iter->current * arr->element_size;
    iter->current++;
    return elem;
}

Lgs_Iterator Lgs_Iterator_fromArray(Lgs_Array* arr) {
    Lgs_Iterator iter;
    iter.container = (void*)arr;
    iter.current = 0;
    iter.entry = NULL;
    iter.hasNext = Lgs_ArrayIter_hasNext;
    iter.next = Lgs_ArrayIter_next;
    iter.reset = Lgs_Iterator_reset;
    return iter;
}
