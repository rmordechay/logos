#include "stmts/LgsReturn.h"

Value* LgsReturn::createIRValue(CodeGenMetadata* metadata) {
    const auto exprIR = expr->getIRValue(metadata);
    return metadata->builder.CreateRet(exprIR);
}

json LgsReturn::asJson() {
    json tree;
    tree["expr"] = expr->asJson();
    return tree;
}

LgsReturn::~LgsReturn() {
    delete expr;
}
