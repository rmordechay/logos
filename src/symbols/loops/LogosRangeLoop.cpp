#include "loops/LogosRangeLoop.h"

#include "loops/LogosLoopVar.h"

#include <LogosStack.h>
#include <exprs/LogosConstant.h>
#include <types/LogosInt.h>

Value* LogosRangeLoop::computeIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    // Init blocks
    const auto irStartRange = startRange->writeIRValue(metadata);
    const auto irEndRange = endRange->writeIRValue(metadata);
    const auto i = builder.CreateAlloca(i32Type);
    builder.CreateStore(irStartRange, i);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto currentVal = builder.CreateLoad(i32Type, i);
    const auto condition = builder.CreateICmpSLT(currentVal, irEndRange);
    loopVar->setIRValue(currentVal);
    builder.CreateCondBr(condition, loopBody, loopEnd);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    metadata->logosStack.addLocalSymbol(loopVar->name, LogosSymbol(LOOP_VAR, loopVar));
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
