#include "stmts/LogosIf.h"

#include "CodeGenerator.h"

Value* LogosIf::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().IRFunc;
    const auto condIR = cond->getIRValue(metadata);
    const auto ifStartBlock = BasicBlock::Create(context, "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(context, "if.end", currentFunc);

    const auto builder = metadata->builder;
    builder->CreateCondBr(condIR, ifStartBlock, ifEndBlock);
    builder->SetInsertPoint(ifStartBlock);

    stmtBlock->getIRValue(metadata);

    builder->CreateBr(ifEndBlock);
    builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}

LogosIf::~LogosIf() {
    delete cond;
    delete stmtBlock;
}
