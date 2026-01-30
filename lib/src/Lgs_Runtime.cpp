#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "LgsUtils.h"
#include <cassert>

#define NANO 1000000000LL

extern "C" void Lgs_Runtime_moveValue(Lgs_TypeKind kind, size_t level, void* left, void* right, size_t size);

extern "C" void Lgs_Runtime_init() {}

extern "C" void Lgs_Runtime_close() {}

extern "C" void Lgs_Runtime_push() {
    const auto level = ++runtime.level;
    runtime.stack.at(level).allocator.level = level;
}

extern "C" void Lgs_Runtime_pop() {
    auto top = runtime.stack.at(runtime.level);
    for (auto [defer, ctx] : top.defers) defer(ctx);
    top.allocator.freeBlocks();
    runtime.level--;
}

extern "C" void* Lgs_Runtime_allocInCurrent(const size_t size, const bool setLevel) {
    return runtime.stack.at(runtime.level).allocator.allocate(size, setLevel);
}

extern "C" void* Lgs_Runtime_allocInLevel(const size_t size, const size_t level, const bool setLevel) {
    return runtime.stack.at(level).allocator.allocate(size, setLevel);
}

extern "C" void* Lgs_Runtime_allocObject(Lgs_Object* type) {
    const auto obj = runtime.stack.at(runtime.level).allocator.allocate(type->size, true);
    const auto typePtr = reinterpret_cast<Lgs_Object**>(static_cast<char*>(obj) + sizeof(size_t));
    *typePtr = type;
    return obj;
}

extern "C" void* Lgs_Runtime_allocDArr(Lgs_TypeInfo* baseType) {
    auto& allocator = runtime.stack.at(runtime.level).allocator;
    const auto arr = allocator.allocate(sizeof(Lgs_DArrayExpr), true);
    const auto dataPtr = Lgs_Runtime_allocInCurrent(baseType->size * LGS_ITER_INIT_CAP, false);
    const auto arrExpr = static_cast<Lgs_DArrayExpr*>(arr);
    arrExpr->baseType = baseType;
    arrExpr->capacity = LGS_ITER_INIT_CAP;
    arrExpr->data = static_cast<char*>(dataPtr);
    return arr;
}

extern "C" void* Lgs_Runtime_allocStrConst(char* str) {
    const auto ptr = runtime.stack.at(0).allocator.allocate(sizeof(Lgs_StrExpr), true);
    static_cast<Lgs_StrExpr*>(ptr)->data = str;
    return ptr;
}

extern "C" void* Lgs_Runtime_reallocate(const void* ptr, const size_t size, const size_t level) {
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
        const auto offset = obj->fields[i].offset;
        void* leftFieldPtr = static_cast<char*>(left) + offset;
        void* rightFieldPtr = static_cast<char*>(right) + offset;
        Lgs_Runtime_moveValue(obj->fields[i].kind, leftLevel, leftFieldPtr, rightFieldPtr, obj->fields[i].size);
    }
}

extern "C" void Lgs_Runtime_moveArr(Lgs_DArrayExpr* leftArr, const Lgs_DArrayExpr* rightArr) {
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

extern "C" void* Lgs_Runtime_moveArrElement(const Lgs_DArrayExpr* arr, void* element) {
    const auto levelArr = arr->level;
    const auto elementLevel = *static_cast<size_t*>(element);
    assert(levelArr <= runtime.level && elementLevel <= runtime.level);
    if (levelArr >= elementLevel) return element;
    if (arr->baseType->kind == RTT_DARRAY) {
        assert(0);
    }
    assert(0);
}

extern "C" void Lgs_Runtime_moveStr(Lgs_StrExpr* left, const Lgs_StrExpr* right) {
    const auto leftLevel = left->level;
    const auto rightLevel = right->level;
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) {
        left->data = right->data;
        return;
    }
    auto& allocator = runtime.stack.at(leftLevel).allocator;
    const auto size = std::strlen(right->data) + 1;
    left->data = static_cast<char*>(allocator.allocate(size, false));
    std::memcpy(left->data, right->data, size);
}

extern "C" void Lgs_Runtime_moveValue(const Lgs_TypeKind kind, const size_t level, void* left, void* right, const size_t size) {
    switch (kind) {
    case RTT_OBJECT: {
        const auto leftField = *static_cast<void**>(left);
        const auto rightField = *static_cast<void**>(right);
        if (leftField) {
            Lgs_Runtime_moveObject(leftField, rightField);
        } else {
            auto& allocator = runtime.stack.at(level).allocator;
            const auto newPtr = allocator.allocate(size, false);
            std::memcpy(newPtr, rightField, size);
            *static_cast<size_t*>(newPtr) = level;
            *static_cast<void**>(left) = newPtr;
        }
        break;
    }
    case RTT_STR: {
        const auto leftStr = static_cast<Lgs_StrExpr*>(left);
        const auto rightStr = static_cast<Lgs_StrExpr*>(right);
        Lgs_Runtime_moveStr(leftStr, rightStr);
        break;
    }
    case RTT_DARRAY: {
        const auto leftArr = static_cast<Lgs_DArrayExpr*>(left);
        const auto rightArr = static_cast<Lgs_DArrayExpr*>(right);
        Lgs_Runtime_moveArr(leftArr, rightArr);
        break;
    }
    case RTT_MAP: {
        assert(0);
    }
    default: {
        std::memcpy(left, right, size);
    }
    }
}

extern "C" void* Lgs_Runtime_getVField(const Lgs_Object* type, void* objInstance, const char* fieldName) {
    for (int i = 0; i < type->fieldsCount; ++i) {
        const auto func = type->fields[i];
        if (std::strcmp(func.name, fieldName) == 0) {
            return static_cast<char*>(objInstance) + func.offset;
        }
    }
    return nullptr;
}

extern "C" void* Lgs_Runtime_getVFunc(const Lgs_Object* type, const char* name) {
    for (int i = 0; i < type->funcsCount; ++i) {
        const auto func = type->funcs[i];
        if (std::strcmp(func.name, name) == 0) {
            return func.ptr;
        }
    }
    return nullptr;
}

extern "C" void Lgs_Runtime_addDefer(const ThunkFunc funcPtr, void* ctx) {
    runtime.stack.at(runtime.level).defers.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_addCoro(const ThunkFunc funcPtr, void* ctx) {
    runtime.coros.emplace_back(Lgs_ThunkFunc{funcPtr, ctx});
}

extern "C" void Lgs_Runtime_throwError(const size_t count, const char* msg, ...) {
    char out[LGS_STR_BUFFER_SIZE];
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
    return static_cast<int64_t>(ts.tv_sec) * NANO + ts.tv_nsec;
}

extern "C" int64_t Lgs_Runtime_timeEnd(const int64_t start) {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    const auto endNano = static_cast<int64_t>(ts.tv_sec) * NANO + ts.tv_nsec;
    return endNano - start;
}

extern "C" size_t Lgs_Runtime_getCurrentLevel() {
    return runtime.level;
}
