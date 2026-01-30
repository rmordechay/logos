#pragma once
#include <iostream>

struct Lgs_TypeInfo;

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

struct Lgs_Field {
    const char* name;
    const size_t size;
    const size_t offset;
    const Lgs_TypeKind kind;
    void* type;
};

struct Lgs_Method {
    const char* name;
    void* ptr;
};

struct Lgs_Object {
    const size_t id;
    const char* name;
    const size_t size;
    const size_t fieldsCount;
    const size_t funcsCount;
    const Lgs_Field* fields;
    const Lgs_Method* funcs;
};

struct Lgs_SArr {
    const size_t length;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Nullable {
    bool isPtr;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Map {
    Lgs_TypeInfo* key;
    Lgs_TypeInfo* value;
};

struct Lgs_TypeInfo {
    const size_t size;
    const Lgs_TypeKind kind;
    union {
        Lgs_Object* object;
        Lgs_SArr* sArr;
        Lgs_Nullable* nullable;
        Lgs_Map* map;
        void* dummy;
    };
};
