#include "loops/LgsRangeLoop.h"
#include "logos/LgsCodeGen.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"

void LgsRangeLoop::createIRLoop(LgsCodeGen* codeGen) {
    initIndex(codeGen);
    codeGen->builder.CreateBr(IRCondBlock);

    // Condition
    codeGen->startBlock(IRCondBlock);
    const auto iValue = loadIndex(codeGen);
    const auto condition = codeGen->builder.CreateICmpSLT(iValue, loopEnd(codeGen));
    setLoopTerminals(codeGen, iValue);
    codeGen->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    codeGen->startBlock(IRBodyBlock);
    loopVars.front()->setIRValue(iValue);
    stmtsBlock->createIRValue(codeGen);
}

Value* LgsRangeLoop::loopStart(LgsCodeGen* codeGen) const {
    if (!startRange) return codeGen->i32Zero();
    return startRange->getIRValue(codeGen);
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen* codeGen) const {
    return endRange->getIRValue(codeGen);
}

void LgsRangeLoop::setLoopTerminals(LgsCodeGen* codeGen, Value* iValue) const {
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
