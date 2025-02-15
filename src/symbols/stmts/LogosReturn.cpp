#include "stmts/LogosReturn.h"

Value* LogosReturn::getLLVMValue(CodeGenMetadata* metadata) {
    const auto exprLLVM = expr->getLLVMValue(metadata);
    llvmValue = metadata->builder->CreateRet(exprLLVM);
    return llvmValue;
}

LogosReturn::~LogosReturn() {
    delete expr;
}
