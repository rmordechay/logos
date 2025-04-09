#include "loops/LgsLoop.h"
#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

Value* LgsLoop::createIRValue(CodeGenMetadata* metadata) {
    initIRLoop(metadata);
    setLoopIRCondition(metadata);
    startBlock(metadata, loopBodyBlock);
    setIRLoopVariable(metadata);
    stmtBlock->createIRValue(metadata);
    exitIRLoop(metadata);
    return nullptr;
}

void LgsLoop::initIRLoop(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope();
    metadata->lgsStack.currentLoop = this;
    auto& builder = metadata->builder;
    loopCondBlock = createBasicBlock(BB_LOOP_CONDITION);
    loopBodyBlock = createBasicBlock(BB_LOOP_BODY);
    loopExitBlock = createBasicBlock(BB_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Ty);
    builder.CreateStore(builder.getInt32(loopStart()), iPtr);
    builder.CreateBr(loopCondBlock);
}

void LgsLoop::setLoopIRCondition(CodeGenMetadata* metadata) {
    startBlock(metadata, loopCondBlock);
    auto& builder = metadata->builder;
    iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto condition = builder.CreateICmpSLT(iValue, builder.getInt32(loopEnd()));
    builder.CreateCondBr(condition, loopBodyBlock, loopExitBlock);
}

void LgsLoop::exitIRLoop(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    // Increment loop variable
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondBlock);
    // Loop exit
    startBlock(metadata, loopExitBlock);
    metadata->lgsStack.currentLoop = nullptr;
    metadata->lgsStack.exitScope();
}

LgsLoop::~LgsLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
