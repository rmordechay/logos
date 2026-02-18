#pragma once

struct Lgs_TypeInfo;
struct Lgs_Map;

struct Lgs_StrExpr {
    size_t level;
    char* data;
};

struct Lgs_DArrExpr {
    size_t level;
    Lgs_TypeInfo* baseType;
    size_t length;
    size_t capacity;
    char* data;
};

struct Lgs_Entry {
    char* key;
    char* value;
    Lgs_Entry* next;
};

struct Lgs_HashMap {
    size_t level;
    Lgs_TypeInfo* type;
    Lgs_Entry** entries;
    size_t len;
    size_t capacity;
};