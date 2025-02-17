#include "stmts/LogosIf.h"

Value* LogosIf::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().IRFunc;
    const auto condIR = cond->getIRValue(metadata);
    const auto ifStartBlock = BasicBlock::Create(context, "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(context, "if.end", currentFunc);

    metadata->builder->CreateCondBr(condIR, ifStartBlock, ifEndBlock);
    metadata->builder->SetInsertPoint(ifStartBlock);

    stmtBlock->getIRValue(metadata);

    metadata->builder->CreateBr(ifEndBlock);
    metadata->builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}

LogosIf::~LogosIf() {
    delete cond;
    delete stmtBlock;
}
