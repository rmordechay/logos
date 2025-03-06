#include "loops/LogosRangeLoop.h"

#include <LogosStack.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosVariable.h>
#include <types/LogosInt.h>

Value* LogosRangeLoop::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = BasicBlock::Create(context, "loop_condition");
    const auto loopBody = BasicBlock::Create(context, "loop_body");
    const auto loopEnd = BasicBlock::Create(context, "loop_end");

    // Init blocks
    const auto irStartRange = startRange->writeIRValue(metadata);
    const auto irEndRange = endRange->writeIRValue(metadata);
    const auto i = builder.CreateAlloca(i32Type, nullptr);
    builder.CreateStore(irStartRange, i);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto currentVal = builder.CreateLoad(i32Type, i);
    const auto condition = builder.CreateICmpSLT(currentVal, irEndRange);
    builder.CreateCondBr(condition, loopBody, loopEnd);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    const auto constant = LOGOS_INT.getConstant();
    constant->setIRValue(currentVal);
    metadata->logosStack.addLocalSymbol(loopVar->name, LogosSymbol(CONSTANT, constant));
    stmtBlock->writeIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(currentVal, builder.getInt32(1));
    builder.CreateStore(inc, i);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopEnd);
    metadata->logosStack.exitScope();
    return nullptr;
}
