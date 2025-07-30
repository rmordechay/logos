#include "loops/LgsRangeLoop.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"

#include "utils/LgsUtils.h"

Value* LgsRangeLoop::loopStart(LgsCodeGen* codeGen) {
    return startRange->getIRValue(codeGen);
}

Value* LgsRangeLoop::loopEnd(LgsCodeGen* codeGen) {
    return endRange->getIRValue(codeGen);
}

void LgsRangeLoop::initIRLoop(LgsCodeGen* codeGen) {
    IRCondBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_LOOP_COND);
    IRBodyBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_LOOP_EXIT);
    iPtr = codeGen->builder.CreateAlloca(codeGen->i32Ty());
    codeGen->builder.CreateStore(loopStart(codeGen), iPtr);
    codeGen->builder.CreateBr(IRCondBlock);

    // Condition
    codeGen->startBlock(IRCondBlock);
    auto iValue = codeGen->builder.CreateLoad(codeGen->i32Ty(), iPtr);
    const auto upperBound = codeGen->builder.CreateZExt(loopEnd(codeGen), codeGen->i32Ty());
    const auto condition = codeGen->builder.CreateICmpSLT(iValue, upperBound);
    codeGen->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    codeGen->startBlock(IRBodyBlock);
    iValue = codeGen->builder.CreateLoad(codeGen->i32Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsRangeLoop::IRLoopPrologue(LgsCodeGen* codeGen) const {
    if (!codeGen->lastInstTerminator()) {
        // Increment loop variable
        const auto iValue = codeGen->builder.CreateLoad(codeGen->i32Ty(), iPtr);
        const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i32(1));
        codeGen->builder.CreateStore(inc, iPtr);
        codeGen->builder.CreateBr(IRCondBlock);
    }
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete endRange;
}
