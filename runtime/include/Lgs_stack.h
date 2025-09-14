#pragma once
#include "Lgs_stack.h"
#include "logos/LgsAppConfigs.h"

typedef void (*Lgs_Defer_Func)(void*);

struct Lgs_Thunk_Func {
    Lgs_Defer_Func func;
    void* ctx;
};

struct Lgs_Stack_Frame {
    Lgs_Thunk_Func defers[LOCALS_CAPACITY];
    Lgs_Thunk_Func coros[LOCALS_CAPACITY];
    int defersCount;
    int corosCount;
};

struct Lgs_Stack {
    int stackIndex;
    Lgs_Stack_Frame frames[STACK_CAPACITY];

    void push();
    void pop();
    void callDefers() const;
    void addDefer(void* funcPtr, void* ctx);
    void addCoro(void* funcPtr, void* ctx);
};
