#include <cstdlib>
#include "Lgs_runtime.h"
#include "Lgs_stack.h"

struct Lgs_runtime {
    Lgs_Stack stack;
};

static Lgs_runtime runtime;

extern "C" {

void Lgs_Stack_push() {
    if (runtime.stack.top + 1 >= STACK_CAPACITY) std::exit(1);
    runtime.stack.top++;
    Lgs_Stack_Frame& frame = runtime.stack.frames[runtime.stack.top];
    frame.defers_count = 0;
    frame.coros_count = 0;
}

void Lgs_Stack_pop() {
    if (runtime.stack.top < 0) std::exit(1);
    runtime.stack.top--;
}

void Lgs_Stack_addDefer(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) std::exit(1);
    auto& top = runtime.stack.frames[runtime.stack.top];
    const Lgs_Thunk_Func func_entry{reinterpret_cast<Lgs_Defer_Func>(funcPtr), ctx};
    top.defers[top.defers_count++] = func_entry;
}

void Lgs_Stack_addCoro(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) std::exit(1);
    auto& top = runtime.stack.frames[runtime.stack.top];
    const Lgs_Thunk_Func func_entry{reinterpret_cast<Lgs_Defer_Func>(funcPtr), ctx};
    top.coros[top.coros_count++] = func_entry;
}

void Lgs_Stack_callDefers() {
    const auto& top = runtime.stack.frames[runtime.stack.top];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}

} // extern "C"