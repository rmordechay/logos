#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>
#include <unordered_set>

struct Lgs_StackFrame {
    std::vector<Lgs_ThunkFunc> defers;
    std::unordered_set<void*> orphans;
};

struct Lgs_Runtime {
    int16_t stackLevel = -1;
    Lgs_Allocator allocator;
    LgsErrHandler errHandler;
    std::unordered_set<void*> owners;
    std::vector<Lgs_ThunkFunc> coros;
    std::array<Lgs_StackFrame, 1024> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

extern "C" void* Lgs_Runtime_allocate(size_t size, bool isOwner);
extern "C" void* Lgs_Runtime_reallocate(void* ptr, size_t size, bool isOwner);

static inline Lgs_Runtime runtime;
