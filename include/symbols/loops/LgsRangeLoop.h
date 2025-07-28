#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsModule* module) override;
    Value* loopEnd(LgsModule* module) override;
    void initIRLoop(LgsModule* module) override;
    void exitIRLoop(LgsModule* module) const override;
    ~LgsRangeLoop() override;
};


