#pragma once
#include "LgsForLoop.h"

class LgsForeachLoop final : public LgsForLoop {
public:
    LgsExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
    void incAndJumpToCond(LgsLLVMGen& cg) override;
    ~LgsForeachLoop() override;
};


