#include "loops/LogosRangeLoop.h"

#include <LogosStack.h>
#include <exprs/LogosConstant.h>
#include <types/LogosInt.h>

Value* LogosRangeLoop::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->logosStack->currentFunc;
    const auto builder = metadata->builder;
    auto& context = builder->getContext();

    const auto irStartRange = startRange->writeIRValue(metadata);
    const auto irEndRange = endRange->writeIRValue(metadata);

    // Init blocks
    const auto counter = builder->CreateAlloca(builder->getInt32Ty(), nullptr);
    builder->CreateStore(irStartRange, counter);
    const auto loopCondBlock = BasicBlock::Create(context, "loop_cond", currentFunc);
    const auto loopBodyBlock = BasicBlock::Create(context, "loop_body", currentFunc);
    const auto afterLoopBlock = BasicBlock::Create(context, "after_loop", currentFunc);

    // Loop condition
    builder->CreateBr(loopCondBlock);
    builder->SetInsertPoint(loopCondBlock);
    const auto currentVal = builder->CreateLoad(builder->getInt32Ty(), counter);
    const auto condition = builder->CreateICmpSLT(currentVal, irEndRange);
    builder->CreateCondBr(condition, loopBodyBlock, afterLoopBlock);

    // Loop body
    metadata->logosStack->enterScope();
    builder->SetInsertPoint(loopBodyBlock);
    LogosConstant logosConstant(&LOGOS_INT, 0);
    logosConstant.setIRValue(currentVal);
    metadata->logosStack->addLocalSymbol("i", LogosSymbol(CONSTANT, &logosConstant));
    stmtBlock->writeIRValue(metadata);

    // Increment loop variable
    const auto incremented = builder->CreateAdd(currentVal, builder->getInt32(1));
    builder->CreateStore(incremented, counter);
    builder->CreateBr(loopCondBlock);
    builder->SetInsertPoint(afterLoopBlock);
    metadata->logosStack->exitScope();

    return nullptr;
}
