#pragma once
#include <iostream>

struct Lgs_TypeInfo;
typedef void (*ThunkFunc)(void*);

enum Lgs_TypeKind {
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
    RTT_VEC2,
    RTT_VEC3,
    RTT_VEC4,
    RTT_MATRIX,
    RTT_SARRAY,
    RTT_DARRAY,
    RTT_SET,
    RTT_MAP,
    RTT_OBJECT,
    RTT_ENUM,
    RTT_TYPE,
    RTT_ANY,
    RTT_NULLABLE,
    RTT_UNKNOWN,
};

struct Lgs_Object {
    size_t fieldsCount;
    uint64_t* fieldHashes;
    Lgs_TypeInfo** fieldTypes;
};

struct Lgs_SArray {
    size_t len;
    Lgs_TypeInfo* baseType;
};

struct Lgs_DArray {
    Lgs_TypeInfo* baseType;
};

struct Lgs_Map {
    Lgs_TypeInfo* keyType;
    Lgs_TypeInfo* valueType;
};

struct Lgs_Vec2 {
    Lgs_TypeInfo* baseType;
};

struct Lgs_Vec3 {
    Lgs_TypeInfo* baseType;
};

struct Lgs_Vec4 {
    Lgs_TypeInfo* baseType;
};

struct Lgs_Matrix {
    size_t rows;
    size_t columns;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Nullable {
    Lgs_TypeInfo* baseType;
};

struct Lgs_TypeInfo {
    size_t size;
    size_t alignment;
    Lgs_TypeKind kind;
    union {
        Lgs_Object obj;
        Lgs_SArray sArray;
        Lgs_DArray dArray;
        Lgs_Map map;
        Lgs_Vec2 vec2;
        Lgs_Vec3 vec3;
        Lgs_Vec4 vec4;
        Lgs_Matrix matrix;
        Lgs_Nullable nullable;
        void* dummy; // used for types that don't need extra information.
    };
};

struct VKey {
    void* instance;
    int32_t virtualID;
    bool operator==(const VKey& other) const noexcept {
        return instance == other.instance && virtualID == other.virtualID;
    }
};

struct VKeyHash {
    size_t operator()(const VKey& k) const noexcept {
        const auto h1 = std::hash<void*>{}(k.instance);
        const auto h2 = std::hash<int32_t>{}(k.virtualID);
        return h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
    }
};

struct Lgs_ThunkFunc {
    ThunkFunc func;
    void* ctx;
};
