#pragma once
#include "Lgs_stack.h"

struct Lgs_runtime {
    Lgs_Stack stack;
};

extern "C" void Lgs_Stack_push();
extern "C" void Lgs_Stack_pop();
extern "C" void Lgs_Stack_addDefer(void* funcPtr, void* ctx);
extern "C" void Lgs_Stack_addCoro(void* funcPtr, void* ctx);
extern "C" void Lgs_Stack_callDefers();

inline Lgs_runtime runtime;
