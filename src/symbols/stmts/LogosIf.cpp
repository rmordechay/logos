#include "stmts/LogosIf.h"

Value* LogosIf::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().llvmFunc;
    const auto condLLVM = cond->getLLVMValue(metadata);
    const auto ifStartBlock = BasicBlock::Create(context, "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(context, "if.end", currentFunc);

    metadata->builder->CreateCondBr(condLLVM, ifStartBlock, ifEndBlock);
    metadata->builder->SetInsertPoint(ifStartBlock);

    stmtBlock->getLLVMValue(metadata);

    metadata->builder->CreateBr(ifEndBlock);
    metadata->builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}

LogosIf::~LogosIf() {
    delete cond;
    delete stmtBlock;
}
