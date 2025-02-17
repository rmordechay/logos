#include "stmts/LogosLoop.h"

#include <stmts/LogosStmtBlock.h>

Value* LogosLoop::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().IRFunc;
    const auto builder = metadata->builder;
    auto& context = builder->getContext();
    const auto entryBlock = BasicBlock::Create(context, "entry", currentFunc);
    const auto loopBlock = BasicBlock::Create(context, "loop", currentFunc);
    const auto exitBlock = BasicBlock::Create(context, "afterloop", currentFunc);

    builder->SetInsertPoint(entryBlock);
    const auto startVal = builder->getInt32(0);
    const auto endVal = builder->getInt32(10);
    const auto stepVal = builder->getInt32(1);

    const auto iPtr = builder->CreateAlloca(builder->getInt32Ty(), nullptr, "i");
    builder->CreateStore(startVal, iPtr);
    builder->CreateBr(loopBlock);

    // Loop block
    builder->SetInsertPoint(loopBlock);
    const auto CurVal = builder->CreateLoad(builder->getInt32Ty(), iPtr, "curval");

    // Loop condition
    const auto Cond = builder->CreateICmpSLT(CurVal, endVal, "loopcond");
    const auto BodyBB = BasicBlock::Create(context, "loopbody", currentFunc);

    // Branch based on condition
    builder->CreateCondBr(Cond, BodyBB, exitBlock);

    // Loop body
    builder->SetInsertPoint(BodyBB);
    // Print or perform operation here (you would call `printf` similarly)
    const auto NextVal = builder->CreateAdd(CurVal, stepVal, "nextval");
    builder->CreateStore(NextVal, iPtr);
    builder->CreateBr(loopBlock);

    stmtBlock->getIRValue(metadata);

    // After loop
    builder->SetInsertPoint(exitBlock);
    return nullptr;
}
