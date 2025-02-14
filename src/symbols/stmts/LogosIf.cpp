#include "stmts/LogosIf.h"

Value* LogosIf::getLLVMValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->theStack->top().currentFunction;
    const auto condLLVM = cond->getLLVMValue(metadata);
    const auto ifStartBlock = BasicBlock::Create(metadata->builder->getContext(), "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(metadata->builder->getContext(), "if.end", currentFunc);

    metadata->builder->CreateCondBr(condLLVM, ifStartBlock, ifEndBlock);
    metadata->builder->SetInsertPoint(ifStartBlock);
    for (const auto& codeNode : stmts) {
        codeNode->getLLVMValue(metadata);
    }
    metadata->builder->CreateBr(ifEndBlock);
    metadata->builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}

LogosIf::~LogosIf() {
    delete cond;
    for (const auto stmt : stmts) {
        delete stmt;
    }
}
