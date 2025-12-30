#pragma once
#include "LgsForLoop.h"

class LgsForeachLoop final : public LgsForLoop {
public:
    LgsExpr* iterExpr = nullptr;
    Value* iterator = nullptr;

    explicit LgsForeachLoop(LgsExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsCgModule& cg) override;
    Value* loopEnd(LgsCgModule& cg) override;
    void incAndJumpToCond(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsForeachLoop() override;
};


