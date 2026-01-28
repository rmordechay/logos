#pragma once
#include "LgsForLoop.h"

class LgsForeachLoop final : public LgsForLoop {
public:
    LgsExpr* iterExpr = nullptr;
    Value* iteratorCounter = nullptr;

    explicit LgsForeachLoop(LgsExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsCodeGen& cg) override;
    Value* loopEnd(LgsCodeGen& cg) override;
    void incAndJumpToCond(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsForeachLoop() override;
};


