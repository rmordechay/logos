#include "loops/LgsForeachLoop.h"
#include "unary/LgsArrayIndex.h"
#include "loops/LgsLoopVar.h"
#include <unary/LgsArray.h>
#include <unary/constants/LgsConst.h>
#include <types/LgsInt.h>

Value* LgsForeachLoop::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    const auto loopBody = createBasicBlock(BB_LOOP_BODY);
    const auto loopEnd = createBasicBlock(BB_LOOP_END);

    // Init blocks
    const auto arrPtr = iterableExpr->getIRValue(metadata);
    const auto iterableSize = iterable->size();
    const auto i = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), i);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto currentVal = builder.CreateLoad(i32Type, i);
    const auto condition = builder.CreateICmpSLT(currentVal, builder.getInt32(iterableSize));
    builder.CreateCondBr(condition, loopBody, loopEnd);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    const auto irType = iterableExpr->type->getIRType();
    const auto lastElement = builder.CreateGEP(irType, arrPtr, currentVal);
    const auto element = builder.CreateLoad(irType, lastElement);
    loopVar->setIRValue(element);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(LOOP_VAR, loopVar));
    stmtBlock->getIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(currentVal, builder.getInt32(1));
    builder.CreateStore(inc, i);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopEnd);
    metadata->logosStack.exitScope();

    return nullptr;
}

LgsForeachLoop::~LgsForeachLoop() {
    if (loopVar) {
        delete loopVar;
    }
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
