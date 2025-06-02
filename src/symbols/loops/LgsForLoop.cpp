#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"
#include "logos/LgsGlobals.h"
#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(Module* module) {
    initIRLoop(module);
    startBlock(module, loopCondBlock);
    setLoopIRCondition(module);
    startBlock(module, loopBodyBlock);
    setIRLoopVars(module);
    stmtBlock->createIRValue(module);
    exitIRLoop(module);
}

void LgsForLoop::initIRLoop(Module* module) {
    runtime.enterScope();
    runtime.stack.top().loop = this;
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
    startBlock(module, loopExitBlock);
    runtime.stack.top().loop = nullptr;
    runtime.exitScope();
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
