#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "Lgs_DArrayExpr.h"
#include "Lgs_SetExpr.h"
#include <cassert>

extern "C" void Lgs_Runtime_freeValue(void* ptr, const Lgs_TypeInfo* type);

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    runtime.stackLevel++;
    std::println("Entering {}", runtime.stackLevel);
}

extern "C" void Lgs_Runtime_pop() {
    std::println("Exiting {}", runtime.stackLevel);
    auto& top = runtime.stack[runtime.stackLevel];
    // Call defers
    for (auto [defer, ctx] : top.defers) defer(ctx);
    // Free allocations
    if (!top.orphans.empty()) {
        for (const auto& [ptr, type] : top.orphans) {
            Lgs_Runtime_freeValue(ptr, type);
        }
        top.orphans.clear();
    }
    runtime.stackLevel--;
}

extern "C" void* Lgs_Runtime_allocate(const size_t size, Lgs_TypeInfo* type, const bool isOwner) {
    const auto ptr = std::malloc(size);
    std::println("Allocated {}B in {}: {}", size, runtime.stackLevel, ptr);
    auto& top = runtime.stack[runtime.stackLevel];
    if (isOwner) {
        top.owners[ptr] = type;
    } else {
        top.orphans[ptr] = type;
    }
    return ptr;
}

extern "C" void Lgs_Runtime_moveValue(void* ptr, const Lgs_TypeInfo* type) {
    for (int i = 0; i < runtime.stackLevel; ++i) {
        auto& frame = runtime.stack[i];
        if (frame.orphans.contains(ptr)) {
            frame.orphans.erase(ptr);
        }
    }
    Lgs_Runtime_freeValue(ptr, type);
}

extern "C" void Lgs_Runtime_freeValue(void* ptr, const Lgs_TypeInfo* type) {
    if (!ptr) return;
    switch (type->kind) {
    case RTT_DARRAY: {
        std::println("Freeing darr {}", ptr);
        std::free(static_cast<Lgs_DArrayExpr*>(ptr)->data);
        break;
    }
    case RTT_SET: {
        std::println("Freeing set {}", ptr);
        std::free(static_cast<Lgs_SetExpr*>(ptr)->data);
        break;
    }
    case RTT_OBJECT: {
        std::println("Freeing {} {}", type->obj.name, ptr);
        break;
    }
    case RTT_STR:
        std::println("Freeing str {}", ptr);
        break;
    case RTT_NULLABLE: {
        std::println("Freeing nullable {}", ptr);
        break;
    }
    case RTT_MAP:
    case RTT_SARRAY:
    default: {
        assert(0);
    }
    }
    std::free(ptr);
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack[runtime.stackLevel].defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addToVTable(void* instance, const int32_t virtualID, void* ptr) {
    runtime.vtable[{instance, virtualID}] = ptr;
}

extern "C" void* Lgs_Runtime_getFromVTable(void* instance, const int32_t virtualID) {
    assert(runtime.vtable.contains(VKey{instance, virtualID}));
    return runtime.vtable[VKey{instance, virtualID}];
}

extern "C" void Lgs_Runtime_throwError(const size_t count, const char* msg, ...) {
    char out[STRING_BUFFER_SIZE];
    va_list args;
    va_start(args, msg);
    formatErrorMsg(msg, out, count, args);
    va_end(args);
    logError(std::string(out) + "\n");
    exit(1);
}
