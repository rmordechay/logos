#include "loops/LgsForeachLoop.h"

#include "stmts/LgsVarDec.h"
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
    const auto arrPtr = iterable->getIRValue(metadata);
    constexpr auto iterableSize = 3;
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
    const auto iterableIRType = iterable->type->getIRType();
    const auto lastElement = builder.CreateGEP(iterableIRType, arrPtr, i);
    const auto element = builder.CreateLoad(iterableIRType, lastElement);
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(element);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
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
    if (iterable) {
        delete iterable;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
