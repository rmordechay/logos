#include "loops/LgsForLoop.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

void LgsForLoop::createIRStmt(CodegenMetadata* metadata) {
    initIRLoop(metadata);
    startBlock(metadata, loopCondBlock);
    setLoopIRCondition(metadata);
    startBlock(metadata, loopBodyBlock);
    setIRLoopVars(metadata);
    stmtBlock->createIRValue(metadata);
    exitIRLoop(metadata);
}

void LgsForLoop::initIRLoop(CodegenMetadata* metadata) {
    metadata->runtime.enterScope();
    metadata->runtime.stack.top().currentLoop = this;
    auto& builder = metadata->builder;
    loopCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION);
    loopBodyBlock = createBasicBlock(LOGOS_LOOP_BODY);
    loopExitBlock = createBasicBlock(LOGOS_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Ty);
    builder.CreateStore(loopStart(metadata), iPtr);
    setIRIterable(metadata);
    builder.CreateBr(loopCondBlock);
}

void LgsForLoop::setLoopIRCondition(CodegenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto upperBound = loopEnd(metadata);
    const auto condition = builder.CreateICmpSLT(iValue, upperBound);
    builder.CreateCondBr(condition, loopBodyBlock, loopExitBlock);
}

void LgsForLoop::exitIRLoop(CodegenMetadata* metadata) const {
    auto& builder = metadata->builder;
    // Increment loop variable
    const auto iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondBlock);
    // Loop exit
    startBlock(metadata, loopExitBlock);
    metadata->runtime.stack.top().currentLoop = nullptr;
    metadata->runtime.exitScope();
}

LgsForLoop::~LgsForLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
