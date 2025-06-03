#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"

#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(Module* module, LgsRuntime* runtime) {
    runtime.stack.enterScope(this);
    initIRLoop(module);
    startBlock(loopCondBlock, nullptr);
    setLoopIRCondition(module);
    startBlock(loopBodyBlock, nullptr);
    setIRLoopVars(module);
    stmtBlock->createIRValue(module, runtime);
    exitIRLoop(module);
    runtime.stack.exitScope(IF_STMT);
}

void LgsForLoop::initIRLoop(Module* module) {
    loopCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION);
    loopBodyBlock = createBasicBlock(LOGOS_LOOP_BODY);
    loopExitBlock = createBasicBlock(LOGOS_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Ty);
    builder.CreateStore(loopStart(module), iPtr);
    setIRIterable(module);
    builder.CreateBr(loopCondBlock);
}

void LgsForLoop::setLoopIRCondition(Module* module) {
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto upperBound = loopEnd(module);
    const auto condition = builder.CreateICmpSLT(iValue, upperBound);
    builder.CreateCondBr(condition, loopBodyBlock, loopExitBlock);
}

void LgsForLoop::exitIRLoop(Module* module) const {
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
