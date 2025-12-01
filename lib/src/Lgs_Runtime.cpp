#include "Lgs_Runtime.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include "Lgs_SetExpr.h"
#include "context/Lgs_Aarch64.h"

#include <cassert>

static void freeValue(void* ptr, const Lgs_TypeInfo* type);
extern "C" void Lgs_Runtime_callDefers();

extern "C" void Lgs_Runtime_init() {

}

extern "C" void Lgs_Runtime_close() {
    runtime.arena.free();
}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.push_back(Lgs_StackFrame{});
}

extern "C" void Lgs_Runtime_pop() {
    // Call defers
    for (auto [func, ctx] : runtime.stack.back().defers) {
        func(ctx);
    }
    // Free values
    for (const auto [ptr, type] : runtime.stack.back().owners) {
        std::cout << "Freeing owner: " << ptr << '\n';
        // freeValue(ptr, type);
    }
    for (const auto [ptr, type] : runtime.stack.back().orphans) {
        std::cout << "Freeing orphan: " << ptr << '\n';
        // freeValue(ptr, type);
    }
    runtime.stack.pop_back();
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.back().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void* Lgs_Runtime_allocate(const size_t size, Lgs_TypeInfo* type, const bool isOwner) {
    const auto ptr = std::malloc(size);
    std::cout << "Allocated: " << size << ' ' << '\n';
    if (isOwner) {
        runtime.stack.back().owners[ptr] = type;
    } else {
        runtime.stack.back().orphans[ptr] = type;
    }
    return ptr;
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    assert(0);
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
    case RTT_DARRAY: {
        const auto darray = static_cast<Lgs_DArrayExpr*>(ptr);
        std::free(darray->data);
        std::free(darray);
        break;
    }
    case RTT_SET: {
        const auto set = static_cast<Lgs_SetExpr*>(ptr);
        std::free(set->data);
        std::free(set);
        break;
    }
    case RTT_STR:
    case RTT_OBJECT: {
        std::free(ptr); return;
    }
    case RTT_SARRAY:
    case RTT_NULLABLE:
    case RTT_MAP: {
        break;
    }
    default: {
        break;
    }
    }
    assert(0);
}
