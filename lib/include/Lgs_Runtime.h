#pragma once
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"
#include <unordered_map>

#include "Lgs_Allocator.h"

#define ALLOCA_SIZE 1024

struct Lgs_StackFrame {
    Lgs_Allocator allocator;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    int64_t level = -1;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::array<Lgs_StackFrame, 1024> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

extern "C" void* Lgs_Runtime_allocate(size_t size);
extern "C" void* Lgs_Runtime_reallocate(void* ptr, size_t size);

static inline Lgs_Runtime runtime;
