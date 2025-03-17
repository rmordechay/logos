#include "loops/LgsForeachLoop.h"

#include "stmts/LgsVarDec.h"
#include "types/LgsArrayType.h"
#include "unary/LgsArrayIndex.h"
#include <unary/LgsArray.h>
#include <types/LgsInt.h>

int LgsForeachLoop::loopSize() {
    return getExprAsIterable()->size();
}

Value* LgsForeachLoop::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    const auto loopBody = createBasicBlock(BB_LOOP_BODY);
    const auto loopExit = createBasicBlock(BB_LOOP_EXIT);

    // Init blocks
    const auto iPtr = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto size = loopSize();
    const auto iValue = builder.CreateLoad(i32Type, iPtr);
    const auto condition = builder.CreateICmpSLT(iValue, builder.getInt32(size));
    builder.CreateCondBr(condition, loopBody, loopExit);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();

    const auto arrValue = iterableExpr->getIRValue(metadata);
    const auto iterableIRType = iterableExpr->type->getIRType(size);
    const auto gep = builder.CreateInBoundsGEP(iterableIRType, arrValue, {builder.getInt32(0), iValue});
    const auto arrayType = dynamic_cast<LgsArrayType*>(iterableExpr->type);
    const auto element = builder.CreateLoad(arrayType->underlyingType->getIRType(), gep);
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(element);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    stmtBlock->getIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopExit);
    metadata->logosStack.exitScope();

    return nullptr;
}

LgsIterable* LgsForeachLoop::getExprAsIterable() const {
    return dynamic_cast<LgsIterable*>(iterableExpr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
