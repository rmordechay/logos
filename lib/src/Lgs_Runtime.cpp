#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <cassert>
#include <complex>

#include "Lgs_Exprs.h"
struct Lgs_DArrayExpr;

static Lgs_StackFrame& getTop();
void moveValue(Lgs_TypeKind kind, size_t level, void* left, void* right, size_t size);

constexpr int64_t nano = 1000000000LL;

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

extern "C" void* Lgs_Runtime_allocate(const size_t size, const size_t level, const bool withLevel) {
    return runtime.stack.at(level).allocator.allocate(size, withLevel);
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

extern "C" void Lgs_Runtime_moveArr(Lgs_DArrayExpr* leftArr, Lgs_DArrayExpr* rightArr) {
    const auto leftLevel = leftArr->level;
    const auto rightLevel = rightArr->level;
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    auto& allocator = runtime.stack.at(leftArr->level).allocator;
    const auto size = rightArr->baseType->size * rightArr->capacity;
    leftArr->length = rightArr->length;
    leftArr->capacity = rightArr->capacity;
    leftArr->data = static_cast<char*>(allocator.allocate(size, false));
    std::memcpy(leftArr->data, rightArr->data, size);
}

extern "C" void* Lgs_Runtime_moveElement(Lgs_DArrayExpr* arr, void* element) {
    const auto levelArr = arr->level;
    const auto elementLevel = *static_cast<size_t*>(element);
    assert(levelArr <= runtime.level && elementLevel <= runtime.level);
    if (levelArr >= elementLevel) return element;
    if (arr->baseType->kind == RTT_DARRAY) {
        assert(0);
    }
    assert(0);
}

extern "C" void Lgs_Runtime_moveObject(void* left, void* right) {
    const auto leftLevel = *static_cast<size_t*>(left);
    const auto rightLevelPtr = static_cast<size_t*>(right);
    const auto rightLevel = *rightLevelPtr;
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    const auto obj = *reinterpret_cast<Lgs_Object**>(rightLevelPtr + 1);
    for (size_t i = 0; i < obj->fieldsCount; ++i) {
        const auto offsets = obj->fieldOffsets;
        void* leftFieldPtr = static_cast<char*>(left) + offsets[i];
        void* rightFieldPtr = static_cast<char*>(right) + offsets[i];
        moveValue(obj->fieldKinds[i], leftLevel, leftFieldPtr, rightFieldPtr, obj->fieldSizes[i]);
    }
}

extern "C" void* Lgs_Runtime_reallocate(const void* ptr, const size_t size, const size_t level) {
    auto& allocator = runtime.stack.at(level).allocator;
    const auto newPtr = allocator.allocate(size, true);
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

void moveValue(const Lgs_TypeKind kind, const size_t level, void* left, void* right, const size_t size) {
    if (kind == RTT_OBJECT) {
        const auto leftField = *static_cast<void**>(left);
        const auto rightField = *static_cast<void**>(right);
        if (leftField) {
            Lgs_Runtime_moveObject(leftField, rightField);
            return;
        }
        auto& allocator = runtime.stack.at(level).allocator;
        const auto newPtr = allocator.allocate(size, false);
        std::memcpy(newPtr, rightField, size);
        *static_cast<size_t*>(newPtr) = level;
        *static_cast<void**>(left) = newPtr;
    } else if (kind == RTT_STR) {
        const auto leftStr = static_cast<Lgs_Str*>(left);
        const auto rightStr = static_cast<Lgs_Str*>(right);
        Lgs_Runtime_moveStr(leftStr, rightStr);
    } else if (kind == RTT_DARRAY) {
        const auto leftArr = static_cast<Lgs_DArrayExpr*>(left);
        const auto rightArr = static_cast<Lgs_DArrayExpr*>(right);
        Lgs_Runtime_moveArr(leftArr, rightArr);
    } else if (kind == RTT_MAP) {
        assert(0);
    } else {
        std::memcpy(left, right, size);
    }
}

static Lgs_StackFrame& getTop() {
    return runtime.stack.at(runtime.level);
}