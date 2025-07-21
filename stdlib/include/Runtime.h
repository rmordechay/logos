#ifndef RUNTIME_H
#define RUNTIME_H

#define STACK_CAPACITY 512
#define STRING_MAX_LEN 1024
#include "Array.h"

typedef struct {
    char data[STRING_MAX_LEN];
    size_t length;
} StackStr;

typedef struct {
    size_t size;
    StackStr items[STACK_CAPACITY];
} Stack;

typedef struct {
    Stack stack;
} Runtime;

void Runtime_init(Runtime* runtime);
void Runtime_push(Runtime* runtime, const char* data);
void Runtime_pop(Runtime* runtime);
void Runtime_print_stack(const Runtime* runtime);
void initArgs(Array* arr, int argc, char** argv);

#endif //RUNTIME_H
