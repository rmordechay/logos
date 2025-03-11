#include "stmts/LogosReturn.h"

Value* LogosReturn::createIRValue(CodeGenMetadata* metadata) {
    const auto exprIR = expr->getIRValue(metadata);
    return metadata->builder.CreateRet(exprIR);
}

LogosReturn::~LogosReturn() {
    delete expr;
}
