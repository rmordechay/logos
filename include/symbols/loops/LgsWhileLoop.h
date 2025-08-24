#pragma once
#include "loops/LgsForLoop.h"

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond_expr) : condExpr(cond_expr) {}
    void incAndJumpToCond(LgsLLVM& codeGen) const override;
    ~LgsWhileLoop() override;
};
