#pragma once
#include "LgsForLoop.h"

class LgsForeachLoop final : public LgsForLoop {
public:
    Value* iterPtr = nullptr;
    LgsExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
    ~LgsForeachLoop() override;
};


