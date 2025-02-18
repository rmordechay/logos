#include "stmts/LogosIf.h"

#include "CodeGenerator.h"

Value* LogosIf::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    metadata->logosStack.enterScope();
    const auto condIR = cond->writeIRValue(metadata);
    const auto ifStartBlock = BasicBlock::Create(context, "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(context, "if.end", currentFunc);

    auto& builder = metadata->builder;
    builder.CreateCondBr(condIR, ifStartBlock, ifEndBlock);
    builder.SetInsertPoint(ifStartBlock);

    stmtBlock->writeIRValue(metadata);

    builder.CreateBr(ifEndBlock);
    builder.SetInsertPoint(ifEndBlock);
    metadata->logosStack.exitScope();
    return nullptr;
}

LogosIf::~LogosIf() {
    delete cond;
    delete stmtBlock;
}
