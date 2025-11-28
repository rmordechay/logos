#include "LgsDefinitions.h"
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include <cassert>
#include "Lgs_HashMap.h"
#include "LgsUtils.h"
#include "context/Lgs_Aarch64.h"
#include <iostream>
#include <stack>

extern "C" void Lgs_Runtime_callDefers();

struct Lgs_Runtime {
    Lgs_Allocator arena;
    std::vector<void*> owners;
    std::vector<void*> orphans;
    std::vector<Lgs_ThunkFunc> coros;
    std::stack<std::vector<Lgs_ThunkFunc>> defers;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {
    runtime.arena.free();
}

extern "C" void Lgs_Runtime_push() {
    runtime.defers.push({});
}

extern "C" void Lgs_Runtime_pop() {
    Lgs_Runtime_callDefers();
    runtime.defers.pop();
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.defers.top().emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_callDefers() {
    for (auto [func, ctx] : runtime.defers.top()) {
        func(ctx);
    }
}

extern "C" void* Lgs_Runtime_allocate(const Lgs_TypeInfo* type, const bool isOwner) {
    const auto ptr = runtime.arena.allocate(type->size);
    if (isOwner) runtime.owners.push_back(ptr);
    else runtime.orphans.push_back(ptr);
    return ptr;
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    auto& top = runtime.defers.top();
}

extern "C" void Lgs_Runtime_yield() {
    Lgs_switchContext();
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
