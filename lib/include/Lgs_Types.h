#pragma once
#include <iostream>

typedef void (*ThunkFunc)(void*);

enum Lgs_TypeKind {
    RTT_ANY,
    RTT_VOID,
    RTT_BOOL,
    RTT_CHAR,
    RTT_STR,
    RTT_BYTE,
    RTT_SHORT,
    RTT_INT,
    RTT_LONG,
    RTT_SIZE,
    RTT_UBYTE,
    RTT_USHORT,
    RTT_UINT,
    RTT_ULONG,
    RTT_FLOAT,
    RTT_DOUBLE,
    RTT_COMPLEX,
    RTT_OBJECT,
    RTT_VEC2,
    RTT_VEC3,
    RTT_VEC4,
    RTT_MATRIX,
    RTT_SARRAY,
    RTT_DARRAY,
    RTT_SET,
    RTT_MAP,
    RTT_ENUM,
    RTT_FUNC,
    RTT_VARIADIC,
    RTT_NULLABLE,
    RTT_UNKNOWN,
};

struct Lgs_TypeInfo {
    const size_t size;
    const Lgs_TypeKind kind;
};

struct Lgs_Field {
    const char* name;
    const size_t size;
    const size_t offset;
    const Lgs_TypeKind kind;
    void* type;
};

struct Lgs_Object {
    const size_t id;
    const char* name;
    const size_t size;
    const size_t fieldsCount;
    const size_t funcsCount;
    const Lgs_Field* fields;
    const void** funcs;
};

struct Lgs_SArr {
    const size_t length;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Nullable {
    bool isPtr;
    Lgs_TypeInfo* baseType;
};

struct VKey {
    void* instance;
    const char* name;
    bool operator==(const VKey& other) const noexcept {
        return instance == other.instance && name == other.name;
    }
};

struct VKeyHash {
    size_t operator()(const VKey& k) const noexcept {
        const auto h1 = std::hash<void*>{}(k.instance);
        const auto h2 = std::hash<const char*>{}(k.name);
        return h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
    }
};

struct Lgs_ThunkFunc {
    ThunkFunc func;
    void* ctx;
};