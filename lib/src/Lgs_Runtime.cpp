#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

#include "Lgs_ArrayExpr.h"

Lgs_StackFrame& getTop();

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {
    runtime.level--;
}

extern "C" void Lgs_Runtime_push() {
    runtime.level++;
}

extern "C" void Lgs_Runtime_pop() {
    auto top = getTop();
    for (auto [defer, ctx] : top.defers) defer(ctx);
    top.allocator.freeBlocks();
    runtime.level--;
}

extern "C" void* Lgs_Runtime_moveReturnValue(const void* rv, const size_t rvSize) {
    auto allocator = runtime.stack.at(runtime.level - 2).allocator;
    const auto newPtr = allocator.allocate(rvSize);
    std::memcpy(newPtr, rv, rvSize);
    return newPtr;
}

extern "C" void* Lgs_Runtime_allocate(const size_t size) {
    return runtime.stack.at(runtime.level).allocator.allocate(size);
}

extern "C" Lgs_Alloc Lgs_Runtime_allocateWithLevel(const size_t size) {
    return Lgs_Alloc{.ptr = runtime.stack.at(runtime.level).allocator.allocate(size), .level = runtime.level};
}

extern "C" void* Lgs_Runtime_move(void* left, void* right, const size_t leftLevel, const size_t rightLevel, const Lgs_TypeInfo* type) {
    if (leftLevel >= rightLevel) {
        std::memcpy(left, right, type->size);
        return left;
    }
    auto& allocator = runtime.stack.at(leftLevel).allocator;
    const auto newPtr = allocator.allocate(type->size);
    if (type->kind == RTT_DARRAY) {
        const auto oldDArr = static_cast<Lgs_ArrayExpr*>(right);
        const auto newDArr = static_cast<Lgs_ArrayExpr*>(newPtr);
        if (oldDArr->length > 0) {
            const auto dataSize = type->dArray.baseType->size * oldDArr->length;
            newDArr->data = static_cast<char*>(allocator.allocate(dataSize));
            std::memcpy(newDArr->data, oldDArr->data, dataSize);
        }
    }
    std::memcpy(newPtr, right, type->size);
    return newPtr;
}

extern "C" void* Lgs_Runtime_reallocate(const void* ptr, const size_t size, const size_t level) {
    auto& allocator = runtime.stack.at(level).allocator;
    const auto newPtr = allocator.allocate(size);
    std::memcpy(newPtr, ptr, size);
    return newPtr;
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    getTop().defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
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

extern "C" int64_t Lgs_Runtime_timeStart() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1000000000LL + ts.tv_nsec;
}

extern "C" int64_t Lgs_Runtime_timeEnd(const int64_t start) {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    const auto endNano = static_cast<int64_t>(ts.tv_sec) * 1000000000LL + ts.tv_nsec;
    return endNano - start;
}

Lgs_StackFrame& getTop() {
    return runtime.stack.at(runtime.level);
}