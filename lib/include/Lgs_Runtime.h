#pragma once
#include "Lgs_Allocator.h"
#include "Lgs_Types.h"
#include "errors/LgsErrHandler.h"

void Lgs_exitWithErrors(const LgsBaseMsg& baseMsg, const std::vector<std::string>& args = {});

struct Lgs_StackFrame {
    std::unordered_map<void*, Lgs_TypeInfo*> owners;
    std::unordered_map<void*, Lgs_TypeInfo*> orphans;
    std::vector<Lgs_ThunkFunc> defers;
};

struct Lgs_Runtime {
    Lgs_Allocator arena;
    LgsErrHandler errHandler;
    std::vector<Lgs_ThunkFunc> coros;
    std::vector<Lgs_StackFrame> stack;
    std::unordered_map<VKey, void*, VKeyHash> vtable;
};

static inline Lgs_Runtime runtime;
