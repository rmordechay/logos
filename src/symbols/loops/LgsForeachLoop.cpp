#include "loops/LgsForeachLoop.h"
#include "unary/LgsArrayIndex.h"
#include <unary/LgsArray.h>
#include <types/LgsInt.h>

Value* LgsForeachLoop::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    const auto loopBody = createBasicBlock(BB_LOOP_BODY);
    const auto loopExit = createBasicBlock(BB_LOOP_EXIT);

    // Init blocks
    const auto arrPtr = iterableExpr->getIRValue(metadata);
    const auto iterableSize = iterable->size();
    const auto iPtr = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto i = builder.CreateLoad(i32Type, iPtr);
    const auto condition = builder.CreateICmpSLT(i, builder.getInt32(iterableSize));
    builder.CreateCondBr(condition, loopBody, loopExit);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    const auto irType = iterableExpr->type->getIRType();
    const auto lastElement = builder.CreateGEP(irType, arrPtr, i);
    const auto element = builder.CreateLoad(irType, lastElement);
    // loopVar->setIRValue(element);
    // metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(LOOP_VAR, loopVar));
    stmtBlock->getIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(i, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopExit);
    metadata->logosStack.exitScope();

    return nullptr;
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
