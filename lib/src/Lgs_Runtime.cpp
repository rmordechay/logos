#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "LgsUtils.h"
#include <cassert>

#include "LgsRTTIndices.h"

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

extern "C" void* Lgs_Runtime_allocObject(Lgs_TypeInfo* type) {
    const auto obj = runtime.stack.at(runtime.level).allocator.allocate(type->size, true);
    const auto typePtr = reinterpret_cast<Lgs_TypeInfo**>(static_cast<char*>(obj) + sizeof(size_t));
    *typePtr = type;
    return obj;
}

extern "C" void* Lgs_Runtime_allocDArr(Lgs_TypeInfo* baseType) {
    auto& allocator = runtime.stack.at(runtime.level).allocator;
    const auto arr = allocator.allocate(sizeof(Lgs_DArrExpr), true);
    const auto dataPtr = Lgs_Runtime_allocInCurrent(baseType->size * LGS_ITER_INIT_CAP, false);
    const auto arrExpr = static_cast<Lgs_DArrExpr*>(arr);
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
    const auto obj = (*reinterpret_cast<Lgs_TypeInfo**>(rightLevelPtr + 1))->object;
    for (size_t i = 0; i < obj->fieldsCount; ++i) {
        const auto offset = obj->fields[i].offset;
        void* leftFieldPtr = static_cast<char*>(left) + offset;
        void* rightFieldPtr = static_cast<char*>(right) + offset;
        Lgs_Runtime_moveValue(obj->fields[i].kind, leftLevel, leftFieldPtr, rightFieldPtr, obj->fields[i].size);
    }
}

extern "C" void Lgs_Runtime_moveArr(Lgs_DArrExpr* leftArr, const Lgs_DArrExpr* rightArr) {
    if (!rightArr) {
        std::memset(leftArr, 0, sizeof(Lgs_DArrExpr));
        return;
    }
    // Left is null
    if (!leftArr->data) {
        leftArr->level = rightArr->level;
        leftArr->baseType = rightArr->baseType;
        leftArr->data = rightArr->data;
        leftArr->length = rightArr->length;
        leftArr->capacity = rightArr->capacity;
        return;
    }

    const auto leftLevel = leftArr->level;
    const auto rightLevel = rightArr->level;
    assert(leftLevel <= runtime.level && rightLevel <= runtime.level);
    if (leftLevel >= rightLevel) {
        leftArr->data = rightArr->data;
        leftArr->length = rightArr->length;
        leftArr->capacity = rightArr->capacity;
    } else {
        auto& allocator = runtime.stack.at(leftArr->level).allocator;
        const auto size = rightArr->baseType->size * rightArr->capacity;
        leftArr->length = rightArr->length;
        leftArr->capacity = rightArr->capacity;
        leftArr->data = static_cast<char*>(allocator.allocate(size, false));
        std::memcpy(leftArr->data, rightArr->data, size);
    }
}

extern "C" void* Lgs_Runtime_moveArrElement(const size_t arrLevel, const Lgs_TypeInfo* baseType, void* element) {
    const auto elementLevel = *static_cast<size_t*>(element);
    assert(arrLevel <= runtime.level && elementLevel <= runtime.level);
    if (arrLevel >= elementLevel) return element;
    auto& allocator = runtime.stack.at(arrLevel).allocator;
    const auto baseSize = baseType->size;
    const auto ptr = allocator.allocate(baseSize, true);
    Lgs_Runtime_moveValue(baseType->kind, arrLevel, ptr, element, baseSize);
    return ptr;
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
        if (left) {
            Lgs_Runtime_moveObject(left, right);
        } else {
            auto& allocator = runtime.stack.at(level).allocator;
            const auto newPtr = allocator.allocate(size, false);
            std::memcpy(newPtr, right, size);
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
        const auto leftArr = static_cast<Lgs_DArrExpr*>(left);
        const auto rightArr = static_cast<Lgs_DArrExpr*>(right);
        Lgs_Runtime_moveArr(leftArr, rightArr);
        break;
    }
    case RTT_NULLABLE:
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

extern "C" size_t Lgs_Runtime_hashValue(const Lgs_TypeInfo* type, void* value) {
    switch (type->kind) {
        case RTT_STR: {
            return hashString(static_cast<char*>(value));
        }
        case RTT_DARRAY: {
            const auto dArr = static_cast<Lgs_DArrExpr*>(value);
            return hashBytes(dArr->data, dArr->length * dArr->baseType->size);
        }
    default: break;
    }
    assert(0);
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

extern "C" void Lgs_Runtime_printBytes(void* ptr, const size_t n) {
    const auto bytes = static_cast<unsigned char*>(ptr);
    for (size_t i = 0; i < n; ++i) {
        printf("%02x", bytes[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

extern "C" bool Lgs_Runtime_canCast(const Lgs_TypeKind t1, const Lgs_TypeKind t2) {
    if (t1 == RTT_FLOAT && t2 == RTT_INT) return true;
    return t1 == t2;
}

extern "C" bool Lgs_Runtime_arrsEqual(const Lgs_DArrExpr* arr1, const Lgs_DArrExpr* arr2) {
    if (arr1->length != arr2->length) return false;
    return std::memcmp(arr1->data, arr2->data, arr1->length * arr1->baseType->size) == 0;
}
