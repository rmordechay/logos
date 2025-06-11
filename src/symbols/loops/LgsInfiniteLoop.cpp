#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsVarDec.h"

void LgsInfiniteLoop::initIRLoop(LgsRuntime* runtime) {
    IRBodyBlock = createBasicBlock(LOGOS_LOOP_BODY, context);
    IRExitBlock = createBasicBlock(LOGOS_LOOP_EXIT, context);
    runtime->builder.CreateBr(IRBodyBlock);
}

void LgsInfiniteLoop::exitIRLoop(LgsRuntime* runtime) const {
    runtime->builder.CreateBr(IRBodyBlock);
    startBlock(runtime, IRExitBlock);
}

Value* LgsInfiniteLoop::loopStart(LgsRuntime* runtime) {
    const auto type = runtime->builder.getIntPtrTy(platform.dataLayout);
    return ConstantInt::get(type, 0);
}

Value* LgsInfiniteLoop::loopEnd(LgsRuntime* runtime) {
    return ConstantInt::getTrue(context);
}

void LgsInfiniteLoop::setIRLoopVars(LgsRuntime* runtime) {
    startBlock(runtime, IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}
