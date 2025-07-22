#include "Runtime.h"
#include "Array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Runtime_init(Runtime* runtime) {
    runtime->stack.size = 0;
}

void Runtime_push(Runtime* runtime, const char* data) {
    Stack* stack = &runtime->stack;
    if (stack->size >= STACK_CAPACITY) assert(false && "stack overflow");
    StackStr* item = &stack->items[stack->size];
    strncpy(item->data, data, STRING_MAX_LEN - 1);
    item->data[STRING_MAX_LEN - 1] = '\0';
    item->length = strlen(item->data);
    stack->size++;
}

void Runtime_pop(Runtime* runtime) {
    Stack* stack = &runtime->stack;
    if (stack->size == 0) exit(1);
    stack->size--;
}

void Runtime_print_stack(const Runtime* runtime) {
    for (int i = runtime->stack.size - 1; i >= 0; --i) {
        const StackStr* item = &runtime->stack.items[i];
        printf("%s\n", item->data);
    }
}

void initArgs(Array* arr, const int argc, char** argv) {
    Array_init(arr, argc, sizeof(char*));
}
