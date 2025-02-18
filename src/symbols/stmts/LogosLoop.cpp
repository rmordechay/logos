#include "stmts/LogosLoop.h"

#include <LogosStack.h>
#include <exprs/LogosExpr.h>

Value* LogosLoop::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().IRFunc;
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

    // // Here you can access the array elements using CurrentIdx
    // // For example:
    // const auto ElementPtr = builder->CreateInBoundsGEP(ArrayType, ConstArray, IdxList);
    // auto CurrentElement = builder->CreateLoad(Type::getInt32Ty(context), ElementPtr);
    //
    // // Your code to process CurrentElement goes here
    //
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
