#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>

struct Lgs_StackFrame {
    std::unordered_map<void*, Lgs_TypeInfo*> owners;
    std::unordered_map<void*, Lgs_TypeInfo*> orphans;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    uint16_t stackLevel = 0;
    Lgs_Allocator allocator;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::array<Lgs_StackFrame, 1024> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;
