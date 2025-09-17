#include "Lgs_stack.h"

void Lgs_stack::push() {
    if (stackIndex + 1 >= STACK_CAPACITY) std::exit(1);
    stackIndex++;
    Lgs_stack_frame& frame = frames[stackIndex];
    frame.defersCount = 0;
    frame.corosCount = 0;
}

void Lgs_stack::pop() {
    if (stackIndex < 0) std::exit(1);
    stackIndex--;
}

void Lgs_stack::addDefer(void* funcPtr, void* ctx) {
    if (stackIndex < 0) std::exit(1);
    const auto deferFunc = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    const Lgs_Thunk_Func func_entry{deferFunc, ctx};
    frames[stackIndex].defers[frames[stackIndex].defersCount++] = func_entry;
}

void Lgs_stack::addCoro(void* funcPtr, void* ctx) {
    if (stackIndex < 0) std::exit(1);
    auto& top = frames[stackIndex];
    const auto deferFunc = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    const Lgs_Thunk_Func func_entry{deferFunc, ctx};
    top.coros[top.corosCount++] = func_entry;
}

void Lgs_stack::callDefers() const {
    const auto& top = frames[stackIndex];
    for (int i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}
