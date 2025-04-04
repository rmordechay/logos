#include "loops/LgsLoop.h"
#include "stmts/LgsStmtBlock.h"
#include "stmts/LgsVarDec.h"

Value* LgsLoop::createIRValue(CodeGenMetadata* metadata) {
    initIRLoop(metadata);
    setLoopIRCondition(metadata);
    startBlock(metadata, loopBody);
    setIRBody(metadata);
    stmtBlock->createIRValue(metadata);
    exitIRLoop(metadata);
    return nullptr;
}

void LgsLoop::initIRLoop(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    metadata->logosStack.currentLoop = this;
    auto& builder = metadata->builder;
    loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    loopBody = createBasicBlock(BB_LOOP_BODY);
    loopExit = createBasicBlock(BB_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Ty);
    builder.CreateStore(builder.getInt32(loopStart()), iPtr);
    builder.CreateBr(loopCondition);
}

void LgsLoop::setLoopIRCondition(CodeGenMetadata* metadata) {
    startBlock(metadata, loopCondition);
    auto& builder = metadata->builder;
    iValue = builder.CreateLoad(i32Ty, iPtr);
    const auto condition = builder.CreateICmpSLT(iValue, builder.getInt32(loopEnd()));
    builder.CreateCondBr(condition, loopBody, loopExit);
}

void LgsLoop::exitIRLoop(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    // Increment loop variable
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondition);
    // Loop exit
    startBlock(metadata, loopExit);
    metadata->logosStack.currentLoop = nullptr;
    metadata->logosStack.exitScope(metadata);
}

LgsLoop::~LgsLoop() {
    for (const auto& loopVar : loopVars) {
        delete loopVar;
    }
}
