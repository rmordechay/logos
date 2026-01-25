#pragma once
#include "errors/LgsErrHandler.h"
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include <unordered_map>

#define ALLOCA_SIZE 1024

struct Lgs_ThunkFunc;

struct Lgs_StackFrame {
    Lgs_Allocator allocator;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    size_t level{};
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::array<Lgs_StackFrame, 1024> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
    std::vector<std::vector<void*>> vtable3;
};

static inline Lgs_Runtime runtime;
