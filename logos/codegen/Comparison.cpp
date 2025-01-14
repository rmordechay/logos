#include "Comparison.h"

#include "exprs/LogosBinaryExpr.h"

#include <iostream>

void Comparison::generateProlog(RuntimeScope* scope) {
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(expr)) {
        Value* symbol = scope->symbols["a"];
        if (auto const allocaInst = static_cast<AllocaInst*>(symbol)) {
            const auto loadInst = builder->CreateLoad(allocaInst->getAllocatedType(), symbol);
            auto currentFrame = scope->currentFrame;
            ifThenBlock = BasicBlock::Create(*context, "if.then", currentFrame);
            ifEndBlock = BasicBlock::Create(*context, "if.end", currentFrame);
            const auto cond = builder->CreateICmpSGT(loadInst, builder->getInt32(10));
            builder->CreateCondBr(cond, ifThenBlock, ifEndBlock);
            builder->SetInsertPoint(ifThenBlock);
        }
    }
}

void Comparison::generateEpilog(RuntimeScope* scope) {
    builder->CreateBr(ifEndBlock);
    builder->SetInsertPoint(ifEndBlock);
}
