#include "loops/LgsRangeLoop.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"

Value* LgsRangeLoop::loopStart(LgsModule* runtime) {
    return rangeStart->getIRValue(runtime);
}

Value* LgsRangeLoop::loopEnd(LgsModule* runtime) {
    return rangeEnd->getIRValue(runtime);
}

void LgsRangeLoop::initIRLoop(LgsModule* runtime) {
    IRCondBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_CONDITION);
    IRBodyBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_EXIT);
    iPtr = runtime->builder.CreateAlloca(runtime->builder.getInt32Ty());
    runtime->builder.CreateStore(loopStart(runtime), iPtr);
    runtime->builder.CreateBr(IRCondBlock);

    // Condition
    startBlock(runtime, IRCondBlock);
    auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto upperBound = runtime->builder.CreateZExt(loopEnd(runtime), runtime->builder.getInt32Ty());
    const auto condition = runtime->builder.CreateICmpSLT(iValue, upperBound);
    runtime->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    startBlock(runtime, IRBodyBlock);
    iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsRangeLoop::exitIRLoop(LgsModule* runtime) const {
    // Increment loop variable
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt32(1));
    runtime->builder.CreateStore(inc, iPtr);
    runtime->builder.CreateBr(IRCondBlock);
    startBlock(runtime, IRExitBlock);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
