#include "LgsDefinitions.h"
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include <cassert>
#include "Lgs_HashMap.h"
#include "LgsUtils.h"
#include "Lgs_Helpers.h"
#include "context/Lgs_Aarch64.h"
#include <iostream>
#include <stack>

static void freeValue(void* ptr, const Lgs_TypeInfo* type);
extern "C" void Lgs_Runtime_callDefers();

struct Lgs_StackFrame {
    std::unordered_map<void*, Lgs_TypeInfo*> owners;
    std::unordered_map<void*, Lgs_TypeInfo*> orphans;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    Lgs_Allocator arena;
    std::vector<Lgs_ThunkFunc> coros;
    std::stack<Lgs_StackFrame> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {
    runtime.arena.free();
}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.push(Lgs_StackFrame{});
}

extern "C" void Lgs_Runtime_pop() {
    Lgs_Runtime_callDefers();
    for (const auto [ptr, type] : runtime.stack.top().owners) {
        freeValue(ptr, type);
    }
    for (const auto [ptr, type] : runtime.stack.top().orphans) {
        freeValue(ptr, type);
    }
    runtime.stack.pop();
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.top().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_callDefers() {
    for (auto [func, ctx] : runtime.stack.top().defers) {
        func(ctx);
    }
}

extern "C" void* Lgs_Runtime_allocate(Lgs_TypeInfo* type, const bool isOwner) {
    const auto ptr = std::malloc(type->size);
    if (isOwner) {
        std::cout << "Allocated owner: " << ptr << '\n';
        runtime.stack.top().owners[ptr] = type;
    } else {
        std::cout << "Allocated orphan: " << ptr << '\n';
        runtime.stack.top().orphans[ptr] = type;
    }
    return ptr;
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {

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

static void freeValue(void* ptr, const Lgs_TypeInfo* type) {
    std::cout << "Freeing: " << ptr << '\n';
    switch (type->kind) {
    case RTT_SARRAY:
        break;
    case RTT_DARRAY:
        break;
    case RTT_SET:
        break;
    case RTT_MAP:
        break;
    case RTT_OBJECT: {
        std::free(ptr);
        return;
    }
    case RTT_NULLABLE:
        break;
    default:
        break;
    }
    assert(0);
}
