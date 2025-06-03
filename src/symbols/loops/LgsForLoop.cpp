#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"
#include "logos/LgsRuntime.h"

#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(this);
    initIRLoop(runtime);
    startBlock(runtime, loopCondBlock, nullptr);
    setLoopIRCondition(runtime);
    startBlock(runtime, loopBodyBlock, nullptr);
    setIRLoopVars(runtime);
    stmtBlock->createIRValue(runtime);
    exitIRLoop(runtime);
    runtime->stack.exitScope(IF_STMT);
}

void LgsForLoop::initIRLoop(LgsRuntime* runtime) {
    loopCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION, context);
    loopBodyBlock = createBasicBlock(LOGOS_LOOP_BODY, context);
    loopExitBlock = createBasicBlock(LOGOS_LOOP_EXIT, context);
    iPtr = runtime->builder.CreateAlloca(runtime->builder.getInt32Ty());
    runtime->builder.CreateStore(loopStart(runtime), iPtr);
    setIRIterable(runtime);
    runtime->builder.CreateBr(loopCondBlock);
}

void LgsForLoop::setLoopIRCondition(LgsRuntime* runtime) {
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto upperBound = loopEnd(runtime);
    const auto condition = runtime->builder.CreateICmpSLT(iValue, upperBound);
    runtime->builder.CreateCondBr(condition, loopBodyBlock, loopExitBlock);
}

void LgsForLoop::exitIRLoop(LgsRuntime* runtime) const {
    // Increment loop variable
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt32(1));
    runtime->builder.CreateStore(inc, iPtr);
    runtime->builder.CreateBr(loopCondBlock);
    // Loop exit
    startBlock(runtime, loopExitBlock, nullptr);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
