#include "loops/LgsInfiniteLoop.h"
#include "data/LgsDefinitions.h"
#include "logos/Platform.h"
#include "stmts/LgsVarDec.h"

Value* LgsInfiniteLoop::loopStart(LgsRuntime* runtime) {
    const auto type = runtime->builder.getIntPtrTy(platform.dataLayout);
    return ConstantInt::get(type, 0);
}

Value* LgsInfiniteLoop::loopEnd(LgsRuntime* runtime) {
    return ConstantInt::getTrue(context);
}

void LgsInfiniteLoop::initIRLoop(LgsRuntime* runtime) {
    IRBodyBlock = createBasicBlock(LOGOS_LOOP_BODY, context);
    IRExitBlock = createBasicBlock(LOGOS_LOOP_EXIT, context);
    runtime->builder.CreateBr(IRBodyBlock);

    startBlock(runtime, IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsInfiniteLoop::exitIRLoop(LgsRuntime* runtime) const {
    runtime->builder.CreateBr(IRBodyBlock);
    startBlock(runtime, IRExitBlock);
}