#pragma once
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* startRange = nullptr;
    LgsExpr* endRange = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : startRange(rangeStart), endRange(rangeEnd) {}
    llvm::Value* loopStart(LgsLLVM* codeGen) const;
    llvm::Value* loopEnd(LgsLLVM* codeGen) const;
    void setLoopTerminals(LgsLLVM* codeGen, llvm::Value* iValue) const;
    ~LgsRangeLoop() override;
};
