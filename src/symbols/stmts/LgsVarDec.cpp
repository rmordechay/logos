#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"

void LgsVarDec::createIRStmt(LgsModule* runtime) {
    const auto IRType = type->getIRType(runtime->context);
    auto exprIRValue = expr->getIRValue(runtime);
    if (shouldLoadIRArg(exprIRValue, expr)) {
        exprIRValue = runtime->builder.CreateLoad(IRType, exprIRValue);
    }
    if (shouldAllocate(IRType)) {
        IRValue = runtime->builder.CreateAlloca(IRType);
        runtime->builder.CreateStore(exprIRValue, IRValue);
    } else {
        IRValue = exprIRValue;
    }
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->asMap() || type->asArray() || expr->asInstance()) return false;
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
}

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}
