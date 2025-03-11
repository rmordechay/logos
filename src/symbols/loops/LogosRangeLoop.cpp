#include "loops/LogosRangeLoop.h"

#include "loops/LogosLoopVar.h"

#include <LogosStack.h>
#include <unary/constants/LogosConstant.h>
#include <types/LogosInt.h>

Value* LogosRangeLoop::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    const auto loopBody = createBasicBlock(BB_LOOP_BODY);
    const auto loopEnd = createBasicBlock(BB_LOOP_END);

    // Init blocks
    const auto irStartRange = startRange->getIRValue(metadata);
    const auto irEndRange = endRange->getIRValue(metadata);
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
