#pragma once
#include "Lgs_Types.h"

struct Lgs_HashMapEntry {
    char* key;
    char* value;
    Lgs_HashMapEntry* next;
};

struct Lgs_HashMap {
    Lgs_HashMapEntry** entries;
    size_t len;
    size_t capacity;
};
