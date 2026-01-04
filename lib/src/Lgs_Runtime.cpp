#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    runtime.stackLevel++;
}

extern "C" void Lgs_Runtime_pop() {
    auto& top = runtime.stack[runtime.stackLevel];
    // Call defers
    for (auto [defer, ctx] : top.defers) defer(ctx);
    // Free allocations
    for (auto alloc : top.allocs) {
        if (!alloc) continue;
        //std::println("Freeing orphan in {}: {}", runtime.stackLevel, alloc);
        std::free(alloc);
    }
    runtime.stackLevel--;
}

extern "C" void* Lgs_Runtime_allocate(const size_t size) {
    const auto ptr = std::malloc(size);
    auto& top = runtime.stack[runtime.stackLevel];
    //std::println("Allocated {}B in {}: {}", size, runtime.stackLevel, ptr);
    top.allocs[top.allocaIndex++] = ptr;
    return ptr;
}

extern "C" void Lgs_Runtime_move(void* ptr) {
    auto& top = runtime.stack[runtime.stackLevel];
    auto& parent = runtime.stack[runtime.stackLevel - 1];
    //std::println("{}", ptr);
}

extern "C" void* Lgs_Runtime_reallocate(void* ptr, const size_t size) {
    const auto newPtr = std::realloc(ptr, size);
    //std::println("Reallocated {}B in {}: {}", size, runtime.stackLevel, newPtr);
    assert(0);
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

extern "C" size_t Lgs_Runtime_hash(const char* str) {
    return hashString(str);
}

extern "C" void Lgs_Runtime_freeValue(void* ptr) {
    //std::println("Freeing in {}: {}", runtime.stackLevel, ptr);
    std::free(ptr);
}
