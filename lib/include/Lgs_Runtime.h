#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>


struct Lgs_StackFrame {
    size_t allocaIndex{};
    std::array<void*, 1024> allocs;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    int16_t stackLevel = -1;
    Lgs_Allocator allocator;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::array<Lgs_StackFrame, 1024> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

extern "C" void* Lgs_Runtime_allocate(size_t size);
extern "C" void* Lgs_Runtime_reallocate(void* ptr, size_t size);

static inline Lgs_Runtime runtime;
