#include "stmts/LgsReturn.h"

Value* LgsReturn::createIRValue(CodeGenMetadata* metadata) {
    const auto exprIR = expr->getIRValue(metadata);
    // metadata->logosStack.freeSymbols(metadata);
    return metadata->builder.CreateRet(exprIR);
}

LgsReturn::~LgsReturn() {
    delete expr;
}
