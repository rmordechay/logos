#include "loops/LogosForeachLoop.h"

#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosVariable.h>
#include <types/LogosInt.h>

Value* LogosForeachLoop::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = BasicBlock::Create(context, "loop_condition");
    const auto loopBody = BasicBlock::Create(context, "loop_body");
    const auto loopEnd = BasicBlock::Create(context, "loop_end");

    // Init blocks
    const auto iPtr = builder.CreateAlloca(i32Type);
    const auto untilPtr = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateStore(builder.getInt32(3), untilPtr);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto i = builder.CreateLoad(i32Type, iPtr);
    const auto until = builder.CreateLoad(i32Type, untilPtr);
    const auto condition = builder.CreateICmpSLT(i, until);
    builder.CreateCondBr(condition, loopBody, loopEnd);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();

    const auto iterableType = iterable->type->getIRType();
    const auto iterableValue = iterable->writeIRValue(metadata);

    const auto elementPtr = builder.CreateGEP(iterableType, iterableValue, i);
    const auto element = builder.CreateLoad(elementPtr->getType(), elementPtr);

    const auto constant = LOGOS_INT.getConstant();
    constant->setIRValue(element);
    metadata->logosStack.addLocalSymbol(loopVar->name, LogosSymbol(CONSTANT, constant));

    stmtBlock->writeIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(i, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopEnd);
    metadata->logosStack.exitScope();

    return nullptr;
}

LogosForeachLoop::~LogosForeachLoop() {
    if (loopVar) {
        delete loopVar;
    }
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (iterable) {
        delete iterable;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
    if (arrayIndex) {
        delete arrayIndex;
    }
}
