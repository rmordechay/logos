#include <stdlib.h>
#include "Lgs_runtime.h"
#include "Lgs_stack.h"

typedef struct {
    Lgs_Stack stack;
} Lgs_runtime;

Lgs_runtime runtime;

void Lgs_Stack_push() {
    if (runtime.stack.top + 1 >= STACK_CAPACITY) exit(1);
    runtime.stack.top++;
    Lgs_Stack_Frame* frame = &runtime.stack.frames[runtime.stack.top];
    frame->defers_count = 0;
    frame->coros_count = 0;
}

void Lgs_Stack_pop(void) {
    if (runtime.stack.top < 0) exit(1);
    runtime.stack.top--;
}

void Lgs_Stack_addDefer(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) exit(1);
    Lgs_Stack_Frame* top = &runtime.stack.frames[runtime.stack.top];
    const Lgs_Thunk_Func func_entry = {.func = funcPtr, .ctx = ctx};
    top->defers[top->defers_count++] = func_entry;
}

void Lgs_Stack_addCoro(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) exit(1);
    Lgs_Stack_Frame* top = &runtime.stack.frames[runtime.stack.top];
    const Lgs_Thunk_Func func_entry = {.func = funcPtr, .ctx = ctx};
    top->coros[top->coros_count++] = func_entry;
}

void Lgs_Stack_callDefers(void) {
    const Lgs_Stack_Frame* top = &runtime.stack.frames[runtime.stack.top];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const Lgs_Thunk_Func funcEntry = top->defers[i];
        if (!funcEntry.func) continue;
        funcEntry.func(funcEntry.ctx);
    }
}
