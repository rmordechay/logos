#pragma once
#include "loops/LgsForLoop.h"
#include "LgsValue.h"

class LgsExpr;

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsCodeGen& cg) override;
    Value* loopEnd(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsStmt* clone() const override;
    ~LgsRangeLoop() override;
};
