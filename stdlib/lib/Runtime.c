#include "Runtime.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024
#define ERROR_STR "\033[1;31mError:\033[0m"
#define STACK_TRACE_NAME_STR "Stack trace:\n"

typedef struct StackFrame {
    const char* func_name;
    const char* path;
    struct StackFrame* previous;
} StackFrame;

typedef struct {
    StackFrame* stack;
} Runtime;

Runtime runtime = {.stack = NULL};

void push_stack_frame(const char* func_name, const char* path) {
    StackFrame* frame = malloc(sizeof(StackFrame));
    frame->func_name = func_name;
    frame->path = path;
    frame->previous = runtime.stack;
    runtime.stack = frame;
}

void pop_stack_frame() {
    StackFrame* prev = runtime.stack->previous;
    free(runtime.stack);
    runtime.stack = prev;
}

void read_strings_from_file(const long pos) {
    FILE* ifs = fopen("paths.dat", "rb");
    fseek(ifs, pos, SEEK_SET);
    int32_t len = 0;
    fread(&len, sizeof(len), 1, ifs);
    char* path = malloc(len + 1);
    fread(path, 1, len, ifs);
    path[len] = '\0';
    fclose(ifs);
    free(path);
}

void print_stack() {
    printf(STACK_TRACE_NAME_STR);
    const StackFrame* frames[STACK_SIZE];
    int count = 0;
    for (const StackFrame* frame = runtime.stack; frame && count < STACK_SIZE; frame = frame->previous) {
        frames[count++] = frame;
    }
    for (int i = count - 1; i >= 0; --i) {
        printf("\t%s at %s\n", frames[i]->func_name, frames[i]->path);
    }
}

void print_error(const char* msg) {
    print_stack();
    printf("%s %s\n", ERROR_STR, msg);
}