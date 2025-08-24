#include "loops/LgsRangeLoop.h"
#include "codegen/LgsLLVM.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsLLVM* codeGen) const {
    if (!startRange) return codeGen->i32Zero();
    return startRange->IRValue;
}

Value* LgsRangeLoop::loopEnd(LgsLLVM* codeGen) const {
    return endRange->IRValue;
}

void LgsRangeLoop::setLoopTerminals(LgsLLVM* codeGen, Value* iValue) const {
    if (isFirst) {
        isFirst->setIRValue(codeGen->builder.CreateICmpEQ(iValue, loopStart(codeGen)));
    }
    if (isLast) {
        const auto decremented = codeGen->builder.CreateSub(loopEnd(codeGen), codeGen->i32(1));
        isLast->setIRValue(codeGen->builder.CreateICmpEQ(iValue, decremented));
    }
}

LgsRangeLoop::~LgsRangeLoop() {
    if (endRange) {
        delete endRange;
        endRange = nullptr;
    }
}
