#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    llvm::Value* loopStart(LgsCodeGen* codeGen) const;
    llvm::Value* loopEnd(LgsCodeGen* codeGen) const;
    void setLoopTerminals(LgsCodeGen* codeGen, llvm::Value* iValue) const;
    void createIRLoop(LgsCodeGen* codeGen) override;
    ~LgsRangeLoop() override;
};
