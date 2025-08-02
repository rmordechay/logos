#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsCodeGen* codeGen) const;
    Value* loopEnd(LgsCodeGen* codeGen) const;
    void setLoopTerminals(LgsCodeGen* codeGen, Value* iValue) const;
    void initIRLoop(LgsCodeGen* codeGen) override;
    ~LgsRangeLoop() override;
};


