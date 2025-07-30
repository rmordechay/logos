#include "loops/LgsInfiniteLoop.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"

Value* LgsInfiniteLoop::loopStart(LgsCodeGen* codeGen) {
    return codeGen->sizeZero();
}

Value* LgsInfiniteLoop::loopEnd(LgsCodeGen* codeGen) {
    return ConstantInt::getTrue(codeGen->context);
}

void LgsInfiniteLoop::initIRLoop(LgsCodeGen* codeGen) {
    IRBodyBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_LOOP_EXIT);
    codeGen->builder.CreateBr(IRBodyBlock);

    codeGen->startBlock(IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsInfiniteLoop::IRLoopPrologue(LgsCodeGen* codeGen) const {
    codeGen->builder.CreateBr(IRBodyBlock);
}
