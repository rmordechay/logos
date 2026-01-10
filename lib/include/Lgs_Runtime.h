#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>

#define ALLOCA_SIZE 200000

struct Lgs_Alloc {
    void* ptr;
    size_t level;
};

struct Lgs_StackFrame {
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    size_t level{};
    Lgs_Alloc allocs[ALLOCA_SIZE];
    Lgs_Allocator allocator;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::vector<Lgs_StackFrame> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

extern "C" void* Lgs_Runtime_allocate(size_t size, bool levelAbove);
extern "C" void* Lgs_Runtime_reallocate(void* ptr, size_t size);

static inline Lgs_Runtime runtime;
