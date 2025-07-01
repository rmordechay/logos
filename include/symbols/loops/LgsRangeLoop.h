#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    Value* loopStart(LgsModule* runtime) override;
    Value* loopEnd(LgsModule* runtime) override;
    void initIRLoop(LgsModule* runtime) override;
    void exitIRLoop(LgsModule* runtime) const override;
    ~LgsRangeLoop() override;
};


