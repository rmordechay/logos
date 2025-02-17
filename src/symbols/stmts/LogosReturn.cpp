#include "stmts/LogosReturn.h"

Value* LogosReturn::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto exprLLVM = expr->getLLVMValue(metadata);
    return metadata->builder->CreateRet(exprLLVM);
}

LogosReturn::~LogosReturn() {
    delete expr;
}
