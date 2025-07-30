#pragma once
#include <stdlib.h>

void push_stack_frame(const char* func_name, const char* path, uint32_t file_path_index);
void pop_stack_frame();
void print_error(const char* msg);
