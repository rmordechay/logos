#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

#include "Lgs_Exprs.h"

constexpr int64_t nano = 1000000000LL;
struct Lgs_DArrayExpr;
static Lgs_StackFrame& getTop();

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

extern "C" void* Lgs_Runtime_allocate(const size_t size, const size_t level) {
    return runtime.stack.at(level).allocator.allocate(size);
}

extern "C" void Lgs_Runtime_moveStr(Lgs_Str* left, const Lgs_Str* right) {
    const auto leftLevel = left->level;
    const auto rightLevel = right->level;
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    auto& allocator = runtime.stack.at(leftLevel).allocator;
    const auto size = std::strlen(right->data) + 1;
    left->data = static_cast<char*>(allocator.allocate(size, false));
    std::memcpy(left->data, right->data, size);
}

extern "C" void Lgs_Runtime_moveObject(void* left, void* right) {
    const auto leftLevel = *static_cast<size_t*>(left);
    const auto rightLevel = *static_cast<size_t*>(right);
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    const auto obj = *reinterpret_cast<Lgs_Object**>(static_cast<size_t*>(left) + 1);
    for (int i = 0; i < obj->fieldsCount; ++i) {
        void* leftFieldPtr = static_cast<char*>(left) + obj->fieldOffsets[i];
        void* rightFieldPtr = static_cast<char*>(right) + obj->fieldOffsets[i];
        if (obj->fieldKinds[i] == RTT_OBJECT) {
            const auto leftField = *static_cast<void**>(leftFieldPtr);
            const auto rightField = *static_cast<void**>(rightFieldPtr);
            if (rightField) {
                if (leftField) {
                    Lgs_Runtime_moveObject(leftField, rightField);
                } else {
                    auto& allocator = runtime.stack.at(leftLevel).allocator;
                    const auto newPtr = allocator.allocate(obj->fieldSizes[i], true);
                    std::memcpy(newPtr, rightField, obj->fieldSizes[i]);
                    *static_cast<size_t*>(newPtr) = leftLevel;
                    *static_cast<void**>(leftFieldPtr) = newPtr;
                }
            } else {
                *static_cast<void**>(leftFieldPtr) = nullptr;
            }
        } else {
            std::memcpy(leftFieldPtr, rightFieldPtr, obj->fieldSizes[i]);
        }
    }
}

extern "C" void* Lgs_Runtime_moveElement(void* iterable, void* element) {
    assert(0);
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
    return static_cast<int64_t>(ts.tv_sec) * nano + ts.tv_nsec;
}

extern "C" int64_t Lgs_Runtime_timeEnd(const int64_t start) {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    const auto endNano = static_cast<int64_t>(ts.tv_sec) * nano + ts.tv_nsec;
    return endNano - start;
}

extern "C" size_t Lgs_Runtime_getCurrentLevel() {
    return runtime.level;
}

extern "C" void Lgs_DArray_initDArray(Lgs_DArrayExpr* arr, const size_t baseSize) {
    auto& allocator = runtime.stack.at(runtime.level).allocator;
    arr->level = runtime.level;
    arr->length = 0;
    arr->capacity = LGS_ITER_INIT_CAP;
    arr->data = static_cast<char*>(allocator.allocate(LGS_ITER_INIT_CAP * baseSize));
}

static Lgs_StackFrame& getTop() {
    return runtime.stack.at(runtime.level);
}