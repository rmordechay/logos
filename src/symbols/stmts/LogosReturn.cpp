#include "stmts/LogosReturn.h"

Value* LogosReturn::computeIRValue(CodeGenMetadata* metadata) {
    const auto exprIR = expr->getIRValue(metadata);
    return metadata->builder->CreateRet(exprIR);
}

LogosReturn::~LogosReturn() {
    delete expr;
}
