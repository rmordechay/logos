#pragma once
#include "loops/LgsForLoop.h"

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond_expr) : condExpr(cond_expr) {}
    void createIRLoop(LgsCodeGen* codeGen) override;
    void incAndJumpToCond(LgsCodeGen* codeGen) const override;
    ~LgsWhileLoop() override = default;
};
