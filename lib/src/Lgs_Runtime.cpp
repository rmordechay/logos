#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

#include "Lgs_ArrayExpr.h"

Lgs_StackFrame& getTop();

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    const auto level = ++runtime.level;
    runtime.stack.at(level).allocator.level = level;
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


struct Obj3 {
    size_t level;
    int id;
};

struct Obj2 {
    size_t level;
    Obj3* obj3;
};

struct Obj1 {
    size_t level;
    Obj2* obj2;
};

extern "C" void Lgs_Runtime_move(void* left, void* right, const Lgs_TypeInfo* type) {
    const auto leftLevel = *static_cast<size_t*>(left);
    const auto rightLevel = *static_cast<size_t*>(right);
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    if (type->kind == RTT_OBJECT) {
        for (int i = 0; i < type->obj.fieldsCount; ++i) {
            const auto fieldType = type->obj.fieldTypes[i];
            const auto fieldOffset = type->obj.fieldOffsets[i];
            void* leftFieldPtr = static_cast<char*>(left) + fieldOffset;
            void* rightFieldPtr = static_cast<char*>(right) + fieldOffset;
            if (fieldType->isHeap) {
                void* l = *static_cast<void**>(leftFieldPtr);
                void* r = *static_cast<void**>(rightFieldPtr);
                Lgs_Runtime_move(l, r, fieldType);
            } else {
                std::memcpy(leftFieldPtr, rightFieldPtr, fieldType->size);
            }
        }
    } else {
        assert(0);
    }
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
