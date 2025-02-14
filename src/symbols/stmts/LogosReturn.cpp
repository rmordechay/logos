#include "stmts/LogosReturn.h"

Value* LogosReturn::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto exprLLVM = expr->writeLLVMValue(metadata);
    llvmValue = metadata->builder->CreateRet(exprLLVM);
    return llvmValue;
}

LogosReturn::~LogosReturn() {
    delete expr;
}
