#include "loops/LgsRangeLoop.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"

void LgsRangeLoop::initIRLoop(LgsCodeGen* codeGen) {
    IRCondBlock = codeGen->createBlock(BLOCK_NAME_LOOP_COND);
    IRBodyBlock = codeGen->createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen->createBlock(BLOCK_NAME_LOOP_EXIT);
    initIndex(codeGen);
    codeGen->builder.CreateBr(IRCondBlock);

    // Condition
    codeGen->startBlock(IRCondBlock);
    auto iValue = loadIndex(codeGen);
    const auto condition = codeGen->builder.CreateICmpSLT(iValue, loopEnd(codeGen));
    setLoopTerminals(codeGen, iValue);
    codeGen->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    codeGen->startBlock(IRBodyBlock);
    iValue = loadIndex(codeGen);
    loopVars[0]->setIRValue(iValue);
}

Value* LgsRangeLoop::loopStart(LgsCodeGen* codeGen) const {
    if (!startRange) return codeGen->i32Zero();
    return startRange->getIRValue(codeGen);
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen* codeGen) const {
    return endRange->getIRValue(codeGen);
}

void LgsRangeLoop::setLoopTerminals(LgsCodeGen* codeGen, Value* iValue) const {
    if (isFirstVarDec) {
        isFirstVarDec->setIRValue(codeGen->builder.CreateICmpEQ(iValue, loopStart(codeGen)));
    }
    if (isLastVarDec) {
        const auto decremented = codeGen->builder.CreateSub(loopEnd(codeGen), codeGen->i32(1));
        isLastVarDec->setIRValue(codeGen->builder.CreateICmpEQ(iValue, decremented));
    }
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete endRange;
}
