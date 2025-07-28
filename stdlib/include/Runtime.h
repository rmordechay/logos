#pragma once

void push_stack_frame(const char* func_name, const char* path);
void pop_stack_frame();
void print_error(const char* msg);
