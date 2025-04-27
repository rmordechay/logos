#include "stmts/LgsReturn.h"

#include "exprs/unary/LgsInstance.h"

Value* LgsReturn::createIRValue(CodeGenMetadata* metadata) {
    if (expr->asInstance()) {
        expr->isReturnValue = true;
        expr->getIRValue(metadata);
        return metadata->builder.CreateRetVoid();
    }
    const auto exprIR = expr->getIRValue(metadata);
    return metadata->builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
