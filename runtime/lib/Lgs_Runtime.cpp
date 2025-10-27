#include "Lgs_Stack.h"
#include "Lgs_Types.h"

#include <cassert>
#include <map>
#include <string>
struct Lgs_DArray;

struct Lgs_Runtime {
    Lgs_Stack stack;
    std::map<void*, std::map<std::string, void*>> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {
}

extern "C" void Lgs_Runtime_close() {
}

extern "C" void Lgs_Stack_addOwner(void* ptr, const Lgs_RTType type) {
    runtime.stack.addOwner(ptr, type);
}

extern "C" void Lgs_Stack_addOrphan(void* ptr, const Lgs_RTType type) {
    runtime.stack.addOrphan(ptr, type);
}

extern "C" void Lgs_Stack_removeOwner(const void* owner) {
    runtime.stack.removeOwner(owner);
}

extern "C" void Lgs_Stack_push() {
    runtime.stack.stackIndex++;
}

extern "C" void Lgs_Stack_pop(const bool cleanup) {
    runtime.stack.pop(cleanup);
}

extern "C" void Lgs_Stack_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_Stack_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_VTable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_VTable_get(void* instancePtr, const char* name) {
    const auto instance = runtime.vtable.find(instancePtr);
    if (instance == runtime.vtable.end()) assert(0);
    const auto method = instance->second.find(name);
    if (method == instance->second.end()) assert(0);
    return method->second;
}
