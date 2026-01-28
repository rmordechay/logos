#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsCodeGen& cg) override;
    Value* loopEnd(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsRangeLoop() override;
};
