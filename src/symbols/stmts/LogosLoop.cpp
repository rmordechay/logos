#include "stmts/LogosLoop.h"

#include <LogosStack.h>
#include <LogosUtils.h>
#include <exprs/LogosExpr.h>
#include <exprs/LogosVariable.h>
#include <stmts/LogosStmtBlock.h>

Value* LogosLoop::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->logosStack->top().IRFunc;
    const auto builder = metadata->builder;
    auto& context = builder->getContext();

    const auto counter = builder->CreateAlloca(Type::getInt32Ty(context), nullptr);
    builder->CreateStore(ConstantInt::get(context, APInt(32, 0)), counter);

    // Create loop blocks
    const auto blockParent = builder->GetInsertBlock()->getParent();
    const auto loopCondBlock = BasicBlock::Create(context, "loop_cond", blockParent);
    const auto loopBodyBlock = BasicBlock::Create(context, "loop_body", blockParent);
    const auto afterLoopBlock = BasicBlock::Create(context, "after_loop", blockParent);

    builder->CreateBr(loopCondBlock);

    // Loop condition
    builder->SetInsertPoint(loopCondBlock);
    const auto CurrentIdx = builder->CreateLoad(Type::getInt32Ty(context), counter);
    const auto Condition = builder->CreateICmpSLT(CurrentIdx, ConstantInt::get(context, APInt(32, 4)));
    builder->CreateCondBr(Condition, loopBodyBlock, afterLoopBlock);

    // Loop body - access current array element
    builder->SetInsertPoint(loopBodyBlock);
    const std::vector<Value*> IdxList = {
        ConstantInt::get(Type::getInt32Ty(context), 0),
        CurrentIdx
    };

    metadata->logosStack->addLocalSymbol(loopVar->name, LogosSymbol::createSymbol(loopVar));

    stmtBlock->getIRValue(metadata);

    // Increment counter
    const auto Incremented = builder->CreateAdd(
        CurrentIdx,
        ConstantInt::get(context, APInt(32, 1)),
        "incremented"
    );
    builder->CreateStore(Incremented, counter);
    builder->CreateBr(loopCondBlock);

    // Set insert point to after loop block
    builder->SetInsertPoint(afterLoopBlock);

    return nullptr;
}
