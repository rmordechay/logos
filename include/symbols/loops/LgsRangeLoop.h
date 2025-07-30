#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsCodeGen* codeGen) override;
    Value* loopEnd(LgsCodeGen* codeGen) override;
    void initIRLoop(LgsCodeGen* codeGen) override;
    void IRLoopPrologue(LgsCodeGen* codeGen) const override;
    ~LgsRangeLoop() override;
};


