#include "Lgs_runtime.h"

extern "C" void Lgs_Vtable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_Vtable_get(void* instancePtr, const char* name) {
    return runtime.vtable[instancePtr][name];
}

extern "C" void Lgs_Stack_push() {
    if (runtime.stack.top + 1 >= STACK_CAPACITY) std::exit(1);
    runtime.stack.top++;
    Lgs_Stack_Frame& frame = runtime.stack.frames[runtime.stack.top];
    frame.defers_count = 0;
    frame.coros_count = 0;
}

extern "C" void Lgs_Stack_pop() {
    if (runtime.stack.top < 0) std::exit(1);
    runtime.stack.top--;
}

extern "C" void Lgs_Stack_addDefer(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) std::exit(1);
    auto& top = runtime.stack.frames[runtime.stack.top];
    const auto deferFunc = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    const Lgs_Thunk_Func func_entry{deferFunc, ctx};
    top.defers[top.defers_count++] = func_entry;
}

extern "C" void Lgs_Stack_addCoro(void* funcPtr, void* ctx) {
    if (runtime.stack.top < 0) std::exit(1);
    auto& top = runtime.stack.frames[runtime.stack.top];
    const auto deferFunc = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    const Lgs_Thunk_Func func_entry{deferFunc, ctx};
    top.coros[top.coros_count++] = func_entry;
}

extern "C" void Lgs_Stack_callDefers() {
    const auto& top = runtime.stack.frames[runtime.stack.top];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}
