#include "Lgs_Runtime.h"
#include "LgsConfigs.h"
#include "Lgs_Exprs.h"
#include "LgsUtils.h"
#include <cassert>
#include "Lgs_Types.h"

#define NANO 1000000000LL
static void moveAndAssign(const Lgs_TypeInfo* fieldType, void* left, void* right, size_t toLevel);
extern "C" void* Lgs_Runtime_moveValue(const Lgs_TypeInfo* type, void* value, size_t toLevel);

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

extern "C" void* Lgs_Runtime_allocStr(char* str) {
    const auto newPtr = runtime.stack.at(0).allocator.allocate(sizeof(Lgs_StrExpr), true);
    const auto newStr = static_cast<Lgs_StrExpr*>(newPtr);
    newStr->data = str;
    return newStr;
}

extern "C" void* Lgs_Runtime_allocEmptyStr(const size_t length) {
    auto& allocator = runtime.stack.at(runtime.level).allocator;
    const auto newPtr = allocator.allocate(sizeof(Lgs_StrExpr), true);
    const auto newStr = static_cast<Lgs_StrExpr*>(newPtr);
    newStr->data = static_cast<char*>(allocator.allocate(length, false));
    return newStr;
}

extern "C" void* Lgs_Runtime_reallocate(const void* ptr, const size_t size, const size_t level) {
    auto& allocator = runtime.stack.at(level).allocator;
    const auto newPtr = allocator.allocate(size, true);
    std::memcpy(newPtr, ptr, size);
    return newPtr;
}

extern "C" void* Lgs_Runtime_moveObject(void* obj, const size_t toLevel) {
    const auto leftLevel = static_cast<size_t*>(obj);
    assert(*leftLevel <= runtime.level && toLevel <= runtime.level);
    if (*leftLevel <= toLevel) return obj;
    auto& allocator = runtime.stack.at(toLevel).allocator;
    const auto objType = (*reinterpret_cast<Lgs_TypeInfo**>(leftLevel + 1))->object;
    const auto newObj = allocator.allocate(objType->size, true);
    for (size_t i = 0; i < objType->fieldsCount; ++i) {
        const auto fieldOffset = objType->fields[i].offset;
        const auto fieldType = objType->fields[i].type;
        void* fieldPtr = static_cast<char*>(obj) + fieldOffset;
        void* newFieldPtr = static_cast<char*>(newObj) + fieldOffset;
        if (fieldType->isHeap) {
            fieldPtr = *static_cast<void**>(fieldPtr);
        }
        moveAndAssign(fieldType, newFieldPtr, fieldPtr, toLevel);
    }
    return newObj;
}

extern "C" void* Lgs_Runtime_moveDArray(Lgs_DArrExpr* arr, const size_t toLevel) {
    if (arr->level <= toLevel) return arr;
    auto& allocator = runtime.stack.at(toLevel).allocator;
    const auto newArr = static_cast<Lgs_DArrExpr*>(allocator.allocate(sizeof(Lgs_DArrExpr), false));
    newArr->level = arr->level;
    newArr->baseType = arr->baseType;
    newArr->length = arr->length;
    newArr->capacity = arr->capacity;
    newArr->data = static_cast<char*>(allocator.allocate(arr->capacity * arr->baseType->size, false));
    for (int i = 0; i < arr->length; ++i) {
        void* element = arr->data + arr->baseType->size * i;
        void* newElement = newArr->data + arr->baseType->size * i;
        if (arr->baseType->isHeap) {
            element = *static_cast<void**>(element);
        }
        moveAndAssign(arr->baseType, newElement, element, toLevel);
    }
    return newArr;
}

extern "C" void* Lgs_Runtime_moveStr(Lgs_StrExpr* strExpr, const size_t toLevel) {
    if (!strExpr) return strExpr;
    const auto leftLevel = strExpr->level;
    assert(leftLevel <= runtime.level && toLevel <= runtime.level);
    if (leftLevel <= toLevel) return strExpr;
    auto& allocator = runtime.stack.at(leftLevel).allocator;
    const auto newStr = static_cast<Lgs_StrExpr*>(allocator.allocate(sizeof(Lgs_StrExpr), false));
    newStr->level = leftLevel;
    newStr->data = static_cast<char*>(allocator.allocate(std::strlen(strExpr->data), false));
    return newStr;
}

extern "C" void* Lgs_Runtime_moveValue(const Lgs_TypeInfo* type, void* value, const size_t toLevel) {
    switch (type->kind) {
    case RTT_OBJECT: return Lgs_Runtime_moveObject(value, toLevel);
    case RTT_DARRAY: return Lgs_Runtime_moveDArray(static_cast<Lgs_DArrExpr*>(value), toLevel);
    case RTT_STR: return Lgs_Runtime_moveStr(static_cast<Lgs_StrExpr*>(value), toLevel);
    case RTT_NULLABLE:
    case RTT_MAP: assert(0);
    default: break;
    }
    return value;
}

static void moveAndAssign(const Lgs_TypeInfo* fieldType, void* left, void* right, const size_t toLevel) {
    const auto ptr = Lgs_Runtime_moveValue(fieldType, right, toLevel);
    if (fieldType->isHeap) {
        *static_cast<void**>(left) = ptr;
    } else {
        std::memcpy(left, ptr, fieldType->size);
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
