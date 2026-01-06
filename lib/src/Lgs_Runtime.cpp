#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

extern "C" size_t Lgs_Runtime_getLevel();
extern "C" void Lgs_Runtime_freeValue(void* ptr);

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.emplace_back(Lgs_StackFrame{});
}

extern "C" void Lgs_Runtime_pop() {
    auto& top = runtime.stack.back();
    // Call defers
    for (auto [defer, ctx] : top.defers) defer(ctx);
    // Free allocations
    for (auto ptr : top.allocs) {
        if (!ptr) continue;
        Lgs_Runtime_freeValue(ptr);
    }
    runtime.stack.pop_back();
}

extern "C" void* Lgs_Runtime_allocate(const size_t size) {
    const auto ptr = std::malloc(size);
    auto& top = runtime.stack.back();
    std::println("Allocated in {}: {}", Lgs_Runtime_getLevel(), ptr);
    top.allocs.insert(ptr);
    return ptr;
}

extern "C" Lgs_Alloc Lgs_Runtime_allocate2(const size_t size, const size_t level) {
    const auto ptr = std::malloc(size);
    auto& top = runtime.stack.back();
    std::println("Allocated in {}: {}", Lgs_Runtime_getLevel(), ptr);
    top.allocs.insert(ptr);
    return Lgs_Alloc{.ptr = ptr, .level = level};
}

extern "C" void Lgs_Runtime_move(const size_t fromLevel, const size_t toLevel, void* ptr, void* expr) {
    std::println("move {} from {} to {} and freeing {}", expr, fromLevel, toLevel, ptr);
    runtime.stack[toLevel].allocs.erase(ptr);
    runtime.stack[fromLevel].allocs.erase(expr);
    runtime.stack[toLevel].allocs.insert(expr);
    Lgs_Runtime_freeValue(ptr);
}

extern "C" void* Lgs_Runtime_reallocate(void* ptr, const size_t size) {
    const auto newPtr = std::realloc(ptr, size);
    std::println("Reallocated {}B in {}: {}", size, Lgs_Runtime_getLevel(), newPtr);
    assert(0);
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.back().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
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

extern "C" size_t Lgs_Runtime_hash(const char* str) {
    return hashString(str);
}

extern "C" void Lgs_Runtime_freeValue(void* ptr) {
    std::println("Freeing in {}: {}", Lgs_Runtime_getLevel(), ptr);
    // std::free(ptr);
}

extern "C" size_t Lgs_Runtime_getLevel() {
    return runtime.stack.size() - 1;
}
