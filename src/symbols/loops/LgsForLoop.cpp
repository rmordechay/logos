#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"

#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(LgsRuntime* runtime) {
    runtime->stack.enterScope(this);
    initIRLoop(runtime);
    startBlock(loopCondBlock, nullptr);
    setLoopIRCondition(runtime);
    startBlock(loopBodyBlock, nullptr);
    setIRLoopVars(runtime);
    stmtBlock->createIRValue(runtime);
    exitIRLoop(runtime);
    runtime->stack.exitScope(IF_STMT);
}

void LgsForLoop::initIRLoop(LgsRuntime* runtime) {
    loopCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION);
    loopBodyBlock = createBasicBlock(LOGOS_LOOP_BODY);
    loopExitBlock = createBasicBlock(LOGOS_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Ty);
    builder.CreateStore(loopStart(runtime), iPtr);
    setIRIterable(runtime);
    builder.CreateBr(loopCondBlock);
}

void LgsForLoop::setLoopIRCondition(LgsRuntime* runtime) {
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto upperBound = loopEnd(runtime);
    const auto condition = builder.CreateICmpSLT(iValue, upperBound);
    builder.CreateCondBr(condition, loopBodyBlock, loopExitBlock);
}

void LgsForLoop::exitIRLoop(LgsRuntime* runtime) const {
    // Increment loop variable
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondBlock);
    // Loop exit
    startBlock(loopExitBlock, nullptr);
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
