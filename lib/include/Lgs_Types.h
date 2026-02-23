#pragma once
#include <cstddef>
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
    RTT_VEC,
    RTT_MATRIX,
    RTT_SARRAY,
    RTT_DARRAY,
    RTT_SET,
    RTT_MAP,
    RTT_ENUM,
    RTT_FUNC,
    RTT_VARIADIC,
    RTT_NULLABLE,
    RTT_FIELD_TYPE,
    RTT_UNKNOWN,
};

struct Lgs_Field {
    const char* name;
    const size_t size;
    const size_t offset;
    const Lgs_TypeKind kind;
    Lgs_TypeInfo* type;
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

struct Lgs_Vec {
    const size_t length;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Matrix {
    const size_t rows;
    const size_t columns;
    Lgs_TypeInfo* baseType;
};

struct Lgs_Map {
    Lgs_TypeInfo* key;
    Lgs_TypeInfo* value;
};

struct Lgs_TypeInfo {
    const char* name;
    const size_t size;
    const Lgs_TypeKind kind;
    const bool isHeap;
    const bool passByRef;
    union {
        Lgs_Object* object;
        Lgs_SArr* sArr;
        Lgs_Vec* vec;
        Lgs_Matrix* mat;
        Lgs_Map* map;
        Lgs_TypeInfo* baseType;
    };
};
