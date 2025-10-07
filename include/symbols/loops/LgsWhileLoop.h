#pragma once
#include "loops/LgsForLoop.h"

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond = nullptr) : condExpr(cond) {}
    void incAndJumpToCond(LgsLLVMGen& cg) override;
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
    ~LgsWhileLoop() override;
};
