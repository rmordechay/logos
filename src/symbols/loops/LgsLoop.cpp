#include "loops/LgsLoop.h"
#include "stmts/LgsStmtBlock.h"

Value* LgsLoop::createIRValue(CodeGenMetadata* metadata) {
    initIRLoop(metadata);
    setIRCondition(metadata);
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    setIRBody(metadata);
    stmtBlock->createIRValue(metadata);
    exitIRLoop(metadata);
    metadata->logosStack.exitScope(metadata);
    return nullptr;
}

void LgsLoop::initIRLoop(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    loopBody = createBasicBlock(BB_LOOP_BODY);
    loopExit = createBasicBlock(BB_LOOP_EXIT);
    iPtr = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateBr(loopCondition);
}

void LgsLoop::setIRCondition(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    startBlock(metadata, loopCondition);
    const auto size = loopSize();
    iValue = builder.CreateLoad(i32Type, iPtr);
    const auto condition = builder.CreateICmpSLT(iValue, builder.getInt32(size));
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
}
