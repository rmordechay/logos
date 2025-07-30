#include "Runtime.h"
#include "LgsConfig.h"
#include "LgsDefinitions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StackFrame {
    const char* func_name;
    const char* path;
    uint32_t file_path_index;
    struct StackFrame* previous;
} StackFrame;

typedef struct {
    StackFrame* stack;
    const char* debug_file;
} Runtime;

Runtime runtime;

void initRuntime(const char* debug_file_path) {
    runtime.stack = NULL;
    runtime.debug_file = debug_file_path;
}

void push_stack_frame(const char* func_name, const char* path, const uint32_t file_path_index) {
    StackFrame* frame = malloc(sizeof(StackFrame));
    frame->func_name = func_name;
    frame->path = path;
    frame->file_path_index = file_path_index;
    frame->previous = runtime.stack;
    runtime.stack = frame;
}

void pop_stack_frame() {
    StackFrame* prev = runtime.stack->previous;
    free(runtime.stack);
    runtime.stack = prev;
}

void read_strings_from_file(const long pos, char* buffer) {
    FILE* ifs = fopen("paths.dat", "rb");
    fseek(ifs, pos, SEEK_SET);
    uint32_t len = 0;
    fread(&len, sizeof(uint32_t), 1, ifs);
    fread(buffer, 1, len, ifs);
    buffer[len] = '\0';
    fclose(ifs);
}

void print_stack() {
    printf("Stack trace:\n");
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
    printf("%s %s\n", LOGOS_ERROR_STR, msg);
    exit(1);
}
