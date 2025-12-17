#pragma once
#include "Lgs_Types.h"

#define LGS_MAP_CAP 1024
#define LGS_MAP_SLOTS_CAP 10

struct Lgs_HashMapEntry {
    char* key;
    char* value;
    bool occupied;
};

struct Lgs_HashMap {
    Lgs_HashMapEntry* entries;
    size_t length;
};

static size_t findSlot(const Lgs_HashMap* map, const char* key);