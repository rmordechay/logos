#pragma once
#include <cmath>

enum Lgs_TypeKind {
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
};

struct Lgs_Object {
    const char* name;
    size_t fieldCount;
    Lgs_TypeKind* fieldTypes;
};

struct Lgs_SArray {
    Lgs_TypeKind baseType;
    size_t length;
};
