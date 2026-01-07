#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>

struct Lgs_Alloc {
    void* ptr;
    size_t level;
};

struct Lgs_StackFrame {
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    Lgs_Allocator allocator;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::vector<Lgs_StackFrame> stack;
    std::unordered_map<void*, size_t> allocs;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

extern "C" void* Lgs_Runtime_allocate(size_t size);
extern "C" void* Lgs_Runtime_reallocate(void* ptr, size_t size);

static inline Lgs_Runtime runtime;
