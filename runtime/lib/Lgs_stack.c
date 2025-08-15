#include "LgsConfig.h"
#include <stdio.h>

typedef void (*Lgs_Defer_Func)(void*);

typedef struct {
    Lgs_Defer_Func func;
    void* ctx;
} Lgs_Thunk_Func;

typedef struct {
    const char* loc;
    Lgs_Thunk_Func defer_funcs[LOCALS_CAPACITY];
    int local_count;
} Lgs_Stack_Frame;

typedef struct {
    Lgs_Stack_Frame frames[STACK_FRAMES_CAPACITY];
    int top;
} Lgs_Stack;

void Lgs_Stack_push(Lgs_Stack* stack, const char* loc) {
    stack->top++;
    Lgs_Stack_Frame* frame = &stack->frames[stack->top];
    frame->loc = loc;
    frame->local_count = 0;
}

static void print_stack(const Lgs_Stack* stack) {
    printf("Stack:\n");
    for (int i = stack->top; i >= 0; --i) {
        printf("\t%s\n", stack->frames[i].loc);
    }
}

void Lgs_Stack_pop(Lgs_Stack* stack) {
    stack->top--;
}

void Lgs_Stack_addDefer(Lgs_Stack* stack, void* funcPtr, void* ctx) {
    Lgs_Stack_Frame* top = &stack->frames[stack->top];
    const Lgs_Thunk_Func func_entry = {.func = funcPtr, .ctx = ctx};
    top->defer_funcs[top->local_count++] = func_entry;
}

void Lgs_Stack_callDefers(const Lgs_Stack* stack) {
    const Lgs_Stack_Frame* top = &stack->frames[stack->top];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const Lgs_Thunk_Func funcEntry = top->defer_funcs[i];
        if (!funcEntry.func) continue;
        funcEntry.func(funcEntry.ctx);
    }
    print_stack(stack);
}
