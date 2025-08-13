#include "LgsConfig.h"

typedef void (*Lgs_Defer_Func)(void*);

typedef struct {
    Lgs_Defer_Func func;
    void* ctx;
} Lgs_Func_Entry;

typedef struct {
    Lgs_Func_Entry defer_funcs[LOCALS_CAPACITY];
    int local_count;
} Lgs_Stack_Frame;

typedef struct {
    Lgs_Stack_Frame frames[STACK_FRAMES_CAPACITY];
    int top;
} Lgs_Stack;

void Lgs_Stack_push(Lgs_Stack* stack) {
    stack->top++;
    Lgs_Stack_Frame* frame = &stack->frames[stack->top];
    frame->local_count = 0;
}

void Lgs_Stack_pop(Lgs_Stack* stack) {
    stack->top--;
}

void Lgs_Stack_addDefer(Lgs_Stack* stack, void* funcPtr, void* ctx) {
    Lgs_Stack_Frame* top = &stack->frames[stack->top];
    const Lgs_Func_Entry func_entry = {.func = funcPtr, .ctx = ctx};
    top->defer_funcs[top->local_count++] = func_entry;
}

void Lgs_Stack_callDefers(const Lgs_Stack* stack) {
    const Lgs_Stack_Frame* top = &stack->frames[stack->top];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const Lgs_Func_Entry funcEntry = top->defer_funcs[i];
        if (!funcEntry.func) continue;
        funcEntry.func(funcEntry.ctx);
    }
}
