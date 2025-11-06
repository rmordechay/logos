#pragma once
#include <cstdint>
#include <cstddef>

enum Lgs_RTType {
    RTT_UNKNOWN,
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
    RTT_SARRAY,
    RTT_DARRAY,
    RTT_SET,
    RTT_MAP,
    RTT_OBJECT,
    RTT_ENUM,
    RTT_TYPE,
    RTT_ANY,
    RTT_NULLABLE,
};

struct Lgs_RTTypeInfo {
    Lgs_RTType kind;
    void* metadata;
};

struct Lgs_Object {
    const char* name;
    size_t fieldCount;
    Lgs_RTType* fieldTypes;
    size_t* fieldOffsets;
};

struct Lgs_SArray {
    Lgs_RTType baseType;
    size_t length;
};

struct Lgs_NullableInt {
    int32_t v;
    bool isSet;
};

struct Lgs_Vec2 {
    float x, y;
};

struct Lgs_Vec3 {
    float x, y, z;
};

struct Lgs_Vec4 {
    float x, y, z, w;
};