#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsInfiniteLoop::loopStart(LgsModule* runtime) {
    const auto type = runtime->builder.getIntPtrTy(dataLayout);
    return ConstantInt::get(type, 0);
}

Value* LgsInfiniteLoop::loopEnd(LgsModule* runtime) {
    return ConstantInt::getTrue(runtime->context);
}

void LgsInfiniteLoop::initIRLoop(LgsModule* runtime) {
    IRBodyBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_EXIT);
    runtime->builder.CreateBr(IRBodyBlock);

    startBlock(runtime, IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsInfiniteLoop::exitIRLoop(LgsModule* runtime) const {
    runtime->builder.CreateBr(IRBodyBlock);
    startBlock(runtime, IRExitBlock);
}