#include "loops/LgsForLoop.h"


#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(LOOP_SCOPE, this);
    initIRLoop(runtime);
    startBlock(runtime, IRCondBlock);
    setLoopIRCondition(runtime);
    startBlock(runtime, IRBodyBlock);
    setIRLoopVars(runtime);
    stmtBlock->createIRValue(runtime);
    exitIRLoop(runtime);
    runtime->stack.exitScope(LOOP_SCOPE);
}

void LgsForLoop::initIRLoop(LgsRuntime* runtime) {
    IRCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION, context);
    IRBodyBlock = createBasicBlock(LOGOS_LOOP_BODY, context);
    IRExitBlock = createBasicBlock(LOGOS_LOOP_EXIT, context);
    iPtr = runtime->builder.CreateAlloca(runtime->builder.getInt32Ty());
    runtime->builder.CreateStore(loopStart(runtime), iPtr);
    setIRIterable(runtime);
    runtime->builder.CreateBr(IRCondBlock);
}

void LgsForLoop::setLoopIRCondition(LgsRuntime* runtime) {
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto upperBound = loopEnd(runtime);
    const auto condition = runtime->builder.CreateICmpSLT(iValue, upperBound);
    runtime->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);
}

void LgsForLoop::exitIRLoop(LgsRuntime* runtime) const {
    // Increment loop variable
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt32(1));
    runtime->builder.CreateStore(inc, iPtr);
    runtime->builder.CreateBr(IRCondBlock);
    // Loop exit
    startBlock(runtime, IRExitBlock);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
