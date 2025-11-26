#include "LgsDefinitions.h"
#include "Lgs_Allocator.h"
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include <cassert>
#include "Lgs_HashMap.h"
#include "LgsUtils.h"
#include "context/Lgs_Aarch64.h"
#include <iostream>

struct Lgs_Runtime {
    Lgs_Stack stack;
    Lgs_Allocator arena;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {

}

extern "C" void Lgs_Runtime_close() {

}

extern "C" void Lgs_Runtime_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_Runtime_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_Runtime_addOwner(void* ptr, const Lgs_TypeInfo* type) {
    runtime.stack.addOwner(ptr, type->kind);
}

extern "C" void Lgs_Runtime_addOrphan(void* ptr, const Lgs_TypeInfo* type) {
    runtime.stack.addOrphan(ptr, type->kind);
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    runtime.stack.removeOwner(owner);
}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.stack.push(Lgs_StackFrame());
}

extern "C" void Lgs_Runtime_pop() {
    runtime.stack.stack.pop();
}

extern "C" void Lgs_Runtime_addCoro(void* funcPtr, void* ctx) {
    runtime.stack.addCoro(funcPtr, ctx);
}

extern "C" void Lgs_Runtime_yield() {
    Lgs_switchContext();
}

extern "C" void* Lgs_Runtime_allocate(const size_t size) {
    return runtime.arena.allocate(size);
}

extern "C" void Lgs_Runtime_addToVTable(void* instance, const int32_t virtualID, void* ptr) {
    runtime.vtable[{instance, virtualID}] = ptr;
}

extern "C" void* Lgs_Runtime_getFromVTable(void* instance, const int32_t virtualID) {
    assert(runtime.vtable.contains(VKey{instance, virtualID}));
    return runtime.vtable[VKey{instance, virtualID}];
}

extern "C" void Lgs_Runtime_throwError(const char* msg) {
    logError(std::string(msg) + "\n");
    exit(1);
}
