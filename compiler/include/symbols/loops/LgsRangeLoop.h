#pragma once
#include "codegen/LgsCodeGen.h"
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsCgModule& cg) override;
    Value* loopEnd(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsRangeLoop() override;
};
