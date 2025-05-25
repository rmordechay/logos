#ifndef RUNTIME_H
#define RUNTIME_H

#define STACK_CAPACITY 512
#define STRING_MAX_LEN 1024

typedef struct {
    char data[STRING_MAX_LEN];
    int length;
} StackStr;

typedef struct {
    StackStr items[STACK_CAPACITY];
    int size;
} Stack;

typedef struct {
    Stack stack;
} Runtime;

#endif //RUNTIME_H
