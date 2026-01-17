#pragma once
#include "LgsConfigs.h"

struct Lgs_SArrayExpr {
    void* data;
    size_t length;
};

struct Lgs_DArrayExpr {
    size_t level;
    char* data;
    size_t length;
    size_t capacity;
};

struct Lgs_HashMap {
    void** entries;
    size_t len;
    size_t capacity;
};
