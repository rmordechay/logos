#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
    LgsStmt* cloneStmt() override;
    ~LgsRangeLoop() override;
};
