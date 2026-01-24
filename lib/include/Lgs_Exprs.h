#pragma once

struct Lgs_TypeInfo;

struct Lgs_Str {
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

struct Lgs_HashMap {
    size_t level;
    void** entries;
    size_t len;
    size_t capacity;
};
