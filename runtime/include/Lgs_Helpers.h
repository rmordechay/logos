#pragma once
#include "Lgs_Types.h"
#include <string>

struct Lgs_Stack;

struct VKey {
    void* instance;
    int32_t virtualID;
    bool operator==(const VKey& other) const noexcept {
        return instance == other.instance && virtualID == other.virtualID;
    }
};

struct VKeyHash {
    size_t operator()(const VKey& k) const noexcept {
        const auto h1 = std::hash<void*>{}(k.instance);
        const auto h2 = std::hash<int32_t>{}(k.virtualID);
        return h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
    }
};

void freeRTType(void* ptr, Lgs_TypeKind type);
void funcCleanup(Lgs_Stack& stack);