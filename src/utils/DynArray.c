#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t element_size;
    int capacity;
    int size;
    void* data;
} Array;

Array* Array_new_Int_Int(const int capacity, const size_t element_size) {
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

void Array_resize_Array(Array* arr) {
    arr->capacity *= 2;
    void* new_data = realloc(arr->data, arr->capacity * arr->element_size);
    if (new_data) {
        arr->data = new_data;
    }
}

void Array_add_Array_Any(Array* arr, const void* value) {
    if (arr->size == arr->capacity) {
        Array_resize_Array(arr);
    }
    char* target = (char*)arr->data + arr->size * arr->element_size;
    memcpy(target, value, arr->element_size);
    arr->size++;
}

void* Array_get_Array_Int(const Array* arr, const int index) {
    if (index < 0 || index >= arr->size) return NULL;
    return (char*)arr->data + (index * arr->element_size);
}

void Array_free_Array(Array* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}

int main() {
    // Array* int_array = Array_new_Int_Int(2, sizeof(int));
    // const int value1 = 42;
    // Array_add_Array_Any(int_array, &value1);
    // printf("Integer at index 0: %d\n", *(int*)Array_get_Array_Int(int_array, 0));
    //
    // Array* double_array = Array_new_Int_Int(2, sizeof(double));
    // const double d1 = 3.14;
    // Array_add_Array_Any(double_array, &d1);
    // printf("Double at index 0: %f\n", *(double*)Array_get_Array_Int(double_array, 0));
    //
    Array* string_array = Array_new_Int_Int(2, sizeof(char*));
    char* s1 = "Hello";
    // char* s2 = "Hello";
    Array_add_Array_Any(string_array, &s1);
    // Array_add_Array_Any(string_array, &s2);
    printf("String at index 0: %s\n", *(char**)Array_get_Array_Int(string_array, 0));
    //
    // Array_free_Array(int_array);
    // Array_free_Array(double_array);
    // Array_free_Array(string_array);
    return 0;
}