#pragma once
#include "loops/LgsForLoop.h"

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond_expr) : condExpr(cond_expr) {}
    void incAndJumpToCond(LgsLLVM& codeGen) override;
    Value* loopStart(LgsLLVM& codeGen) override;
    Value* loopEnd(LgsLLVM& codeGen) override;
    ~LgsWhileLoop() override;
};
