#pragma once
#include "errors/LgsErrHandler.h"
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"

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
};

static inline Lgs_Runtime runtime;