#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    Value* loopStart(LgsModule* module) override;
    Value* loopEnd(LgsModule* module) override;
    void initIRLoop(LgsModule* module) override;
    void exitIRLoop(LgsModule* module) const override;
    ~LgsRangeLoop() override;
};


