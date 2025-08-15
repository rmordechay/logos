#pragma once
#include "Lgs_stack.h"

#include "LgsConfig.h"

typedef void (*Lgs_Defer_Func)(void*);

typedef struct {
    Lgs_Defer_Func func;
    void* ctx;
} Lgs_Thunk_Func;

typedef struct {
    Lgs_Thunk_Func defers[LOCALS_CAPACITY];
    Lgs_Thunk_Func coros[LOCALS_CAPACITY];
    int defers_count;
    int coros_count;
} Lgs_Stack_Frame;

typedef struct {
    Lgs_Stack_Frame frames[STACK_CAPACITY];
    int top;
} Lgs_Stack;
