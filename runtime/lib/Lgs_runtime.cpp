#include "Lgs_stack.h"
#include "Lgs_types.h"

struct Lgs_darray;

struct Lgs_runtime {
    Lgs_stack stack;
    std::map<void*, std::map<std::string, void*>> vtable;
};

static inline Lgs_runtime runtime;

extern "C" void Lgs_runtime_init() {
}

extern "C" void Lgs_runtime_close() {
}

extern "C" void Lgs_stack_addOwner(void* ptr, const Lgs_rttype type) {
    runtime.stack.addOwner(ptr, type);
}

extern "C" void Lgs_stack_addOrphan(void* ptr, const Lgs_rttype type) {
    runtime.stack.addOrphan(ptr, type);
}

extern "C" void Lgs_stack_removeOwner(const void* owner) {
    runtime.stack.removeOwner(owner);
}

extern "C" void Lgs_stack_push() {
    runtime.stack.push();
}

extern "C" void Lgs_stack_pop(const bool cleanup) {
    runtime.stack.pop(cleanup);
}

extern "C" void Lgs_stack_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_stack_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_vtable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_vtable_get(void* instancePtr, const char* name) {
    const auto instance = runtime.vtable.find(instancePtr);
    if (instance == runtime.vtable.end()) assert(0);
    const auto method = instance->second.find(name);
    if (method == instance->second.end()) assert(0);
    return method->second;
}
