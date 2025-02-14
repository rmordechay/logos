#include "stmts/LogosReturn.h"

Value* LogosReturn::getLLVMValue(CodeGenMetadata* metadata) {
    const auto exprLLVM = expr->getLLVMValue(metadata);
    return metadata->builder->CreateRet(exprLLVM);
}

LogosReturn::~LogosReturn() {
    delete expr;
}
