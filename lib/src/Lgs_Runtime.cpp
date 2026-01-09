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

extern "C" void Lgs_Runtime_pop(void* rv) {
    //auto start = std::chrono::high_resolution_clock::now();
    auto& top = runtime.stack.back();
    // Call defers
    for (auto [defer, ctx] : top.defers) defer(ctx);
    // Free allocations
    const auto level = Lgs_Runtime_getLevel();
    if (rv) {
        runtime.allocs[rv] = level - 1;
    }
    std::erase_if(runtime.allocs, [&level](const std::pair<void*, size_t>& pair) {
        const auto equalLevel = pair.second == level;
        if (equalLevel) Lgs_Runtime_freeValue(pair.first);
        return equalLevel;
    });
    runtime.stack.pop_back();
    // const auto end = std::chrono::high_resolution_clock::now();
    // const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    // std::println("{}", duration.count());
}

extern "C" void* Lgs_Runtime_allocate(const size_t size, const bool levelAbove) {
    const auto ptr = std::malloc(size);
    // std::println("Allocated: {}", ptr);
    runtime.allocs[ptr] = Lgs_Runtime_getLevel() - levelAbove;
    return ptr;
}

extern "C" void Lgs_Runtime_move(void* left, void* right) {
    auto& leftLevel = runtime.allocs[left];
    auto& rightLevel = runtime.allocs[right];
    if (leftLevel < rightLevel) {
        rightLevel = leftLevel;
        //std::println("Move right {} to {}", right, leftLevel);
    }
    leftLevel = Lgs_Runtime_getLevel();
    //std::println("Move left {} to {}", left, Lgs_Runtime_getLevel());
}

extern "C" void* Lgs_Runtime_reallocate(void* ptr, const size_t size) {
    assert(0);
}

extern "C" void Lgs_Runtime_freeValue(void* ptr) {
    // std::println("Freeing {} {}", ptr, Lgs_Runtime_getLevel());
    std::free(ptr);
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.back().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addToVTable(void* instance, const char* name, void* ptr) {
    runtime.vtable[{instance, name}] = ptr;
}

extern "C" void* Lgs_Runtime_getFromVTable(void* instance, const char* name) {
    return runtime.vtable[{instance, name}];
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

extern "C" size_t Lgs_Runtime_getLevel() {
    return runtime.stack.size() - 1;
}
