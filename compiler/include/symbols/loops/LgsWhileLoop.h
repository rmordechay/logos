#pragma once
#include "loops/LgsForLoop.h"
#include "LgsValue.h"

class LgsExpr;

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond = nullptr) : condExpr(cond) {}
    void incAndJumpToCond(LgsCodeGen& cg) override;
    Value* loopStart(LgsCodeGen& cg) override;
    Value* loopEnd(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsWhileLoop() override;
};
