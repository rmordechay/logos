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
void moveObject(void* left, void* right, const Lgs_Object* obj);

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

extern "C" void Lgs_Runtime_move(void* left, void* right, const Lgs_TypeInfo* type) {
    const auto leftLevel = *static_cast<uint32_t*>(left);
    const auto rightLevel = *static_cast<uint32_t*>(right);
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return;
    if (type->kind == RTT_OBJECT) {
        moveObject(left, right, &type->obj);
    } else {
        assert(0);
    }
}

extern "C" void* Lgs_Runtime_moveElement(void* iterable, void* element, const Lgs_TypeInfo* type) {
    const auto leftLevel = *static_cast<uint32_t*>(iterable);
    const auto rightLevel = *static_cast<uint32_t*>(element);
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) return element;
    const auto baseType = type->dArray.baseType;
    assert(baseType->isHeap);
    const auto ptr = runtime.stack.at(leftLevel).allocator.allocate(baseType->size);
    if (baseType->kind == RTT_OBJECT) {
        moveObject(ptr, element, &baseType->obj);
    } else {
        assert(0);
    }
    return ptr;
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

extern "C" void Lgs_DArray_initDArray(Lgs_DArrayExpr* arr, const size_t dataSize) {
    auto& allocator = runtime.stack.at(runtime.level).allocator;
    arr->level = runtime.level;
    arr->capacity = LGS_MAP_INITIAL_CAPACITY;
    arr->length = 0;
    arr->data = static_cast<char*>(allocator.allocate(dataSize));
}

void moveObject(void* left, void* right, const Lgs_Object* obj) {
    const auto fieldsCount = obj->fieldsCount;
    const auto fieldTypes = obj->fieldTypes;
    const auto fieldOffsets = obj->fieldOffsets;
    for (int i = 0; i < fieldsCount; ++i) {
        const auto fieldType = fieldTypes[i];
        const auto fieldOffset = fieldOffsets[i];
        void* leftFieldPtr = static_cast<char*>(left) + fieldOffset;
        void* rightFieldPtr = static_cast<char*>(right) + fieldOffset;
        if (fieldType->isHeap) {
            Lgs_Runtime_move(*static_cast<void**>(leftFieldPtr), *static_cast<void**>(rightFieldPtr), fieldType);
        } else {
            std::memcpy(leftFieldPtr, rightFieldPtr, fieldType->size);
        }
    }
}


static Lgs_StackFrame& getTop() {
    return runtime.stack.at(runtime.level);
}