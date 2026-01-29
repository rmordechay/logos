#pragma once

struct Lgs_TypeInfo;
struct Lgs_Map;

struct Lgs_StrExpr {
    size_t level;
    char* data;
};

struct Lgs_NullableExpr {
    int32_t v;
    bool isSet;
};

struct Lgs_DArrayExpr {
    size_t level;
    Lgs_TypeInfo* baseType;
    char* data;
    size_t length;
    size_t capacity;
};

struct Lgs_Entry {
    void* key;
    void* value;
    void* next;
};

struct Lgs_HashMap {
    size_t level;
    Lgs_Map* type;
    Lgs_Entry** entries;
    size_t len;
    size_t capacity;
};