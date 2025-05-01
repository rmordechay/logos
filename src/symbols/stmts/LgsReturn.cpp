#include "stmts/LgsReturn.h"

#include "exprs/unary/LgsInstance.h"

void LgsReturn::createIRStmt(CodeGenMetadata* metadata) {
    if (expr->type->asObject()) {
        expr->initIRValue(metadata);
        metadata->builder.CreateRetVoid();
    }
    const auto exprIR = expr->getIRValue(metadata);
    metadata->builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
