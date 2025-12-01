#pragma once
#include "loops/LgsForLoop.h"

class LgsWhileLoop final : public LgsForLoop {
public:
    LgsExpr* condExpr;

    explicit LgsWhileLoop(LgsExpr* cond = nullptr) : condExpr(cond) {}
    void incAndJumpToCond(LgsCgModule& cg) override;
    Value* loopStart(LgsCgModule& cg) override;
    Value* loopEnd(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsWhileLoop() override;
};
