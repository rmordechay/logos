#include "Runtime.h"
#include "LgsConfig.h"
#include "LgsDefinitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct StackFrame {
    uint64_t file_path_index;
    uint64_t func_name_index;
    struct StackFrame* previous;
} StackFrame;

typedef struct {
    StackFrame* stack;
    const char* debug_file;
} Runtime;

Runtime runtime;

void init_runtime(const char* debug_file) {
    runtime.stack = NULL;
    runtime.debug_file = debug_file;
}

void push_stack_frame(const uint64_t file_path_index, const uint64_t func_name_index) {
    StackFrame* frame = malloc(sizeof(StackFrame));
    frame->file_path_index = file_path_index;
    frame->func_name_index = func_name_index;
    frame->previous = runtime.stack;
    runtime.stack = frame;
}

void pop_stack_frame() {
    if (!runtime.stack) return;
    StackFrame* prev = runtime.stack->previous;
    free(runtime.stack);
    runtime.stack = prev;
}

void read_strings_from_file(FILE* debug_file, const uint64_t pos, char buffer[1024]) {
    fseek(debug_file, pos, SEEK_SET);
    uint64_t len = 0;
    fread(&len, sizeof(uint64_t), 1, debug_file);
    fread(buffer, 1, len, debug_file);
    buffer[len] = '\0';
}

void print_stack() {
    printf("Stack trace:\n");
    const StackFrame* frames[STACK_SIZE];
    int count = 0;
    for (const StackFrame* frame = runtime.stack; frame && count < STACK_SIZE; frame = frame->previous) {
        frames[count++] = frame;
    }
    FILE* debug_file = fopen(runtime.debug_file, "rb");
    for (int i = count - 1; i >= 0; --i) {
        char path[1024];
        char cwd[1024];
        char funcName[1024];
        getcwd(cwd, sizeof(cwd));
        read_strings_from_file(debug_file, frames[i]->file_path_index, path);
        read_strings_from_file(debug_file, frames[i]->func_name_index, funcName);
        printf("\t%s at %s/%s\n", funcName, cwd, path);
    }
    fclose(debug_file);
}

void print_error(const char* msg) {
    print_stack();
    printf("%s %s\n", LOGOS_ERROR_STR, msg);
    exit(1);
}
