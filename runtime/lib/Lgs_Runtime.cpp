#include "LgsDefinitions.h"
#include "Lgs_Allocator.h"
#include "Lgs_Scheduler.h"
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include <cassert>
#include "Lgs_Map.h"
#include <iostream>

weakf Lgs_SArray Lgs_RTTypes_Arrays[] = {};

struct VKey {
    void* instance;
    int32_t virtualID;
    bool operator==(const VKey& other) const noexcept {
        return instance == other.instance && virtualID == other.virtualID;
    }
};

struct VKeyHash {
    size_t operator()(const VKey& k) const noexcept {
        const auto h1 = std::hash<void*>{}(k.instance);
        const auto h2 = std::hash<int32_t>{}(k.virtualID);
        return h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
    }
};

struct Lgs_Runtime {
    Lgs_Stack stack;
    Lgs_Allocator arena;
    Lgs_Scheduler scheduler;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {
    // runtime.scheduler.start();
}

extern "C" void Lgs_Runtime_close() {
    // runtime.scheduler.shutdown();
}

extern "C" void Lgs_Runtime_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_Runtime_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_Runtime_addOwner(void* ptr, const Lgs_TypeKind type) {
    runtime.stack.addOwner(ptr, type);
}

extern "C" void Lgs_Runtime_addOrphan(void* ptr, const Lgs_TypeKind type) {
    runtime.stack.addOrphan(ptr, type);
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    runtime.stack.removeOwner(owner);
}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.stackIndex++;
}

extern "C" void Lgs_Runtime_pop(const bool cleanup) {
    runtime.stack.pop(cleanup);
}

extern "C" void Lgs_Runtime_addCoro(void* funcPtr, void* ctx) {
    runtime.scheduler.spawn(reinterpret_cast<ThunkFunc>(funcPtr), ctx);
}

extern "C" void Lgs_Runtime_yield() {
    runtime.scheduler.yield();
}

extern "C" bool Lgs_Runtime_shouldYield() {
    return runtime.scheduler.shouldYield();
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

extern "C" void Lgs_Runtime_printStackTrace() {
    runtime.stack.printStackTrace();
}
