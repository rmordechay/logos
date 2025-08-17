#pragma once
#include "Lgs_stack.h"
#include "configs/LgsConfig.h"

typedef void (*Lgs_Defer_Func)(void*);

struct Lgs_Thunk_Func {
    Lgs_Defer_Func func;
    void* ctx;
};

struct Lgs_Stack_Frame {
    Lgs_Thunk_Func defers[LOCALS_CAPACITY];
    Lgs_Thunk_Func coros[LOCALS_CAPACITY];
    int defers_count;
    int coros_count;
};

struct Lgs_Stack {
    Lgs_Stack_Frame frames[STACK_CAPACITY];
    int top;
};
