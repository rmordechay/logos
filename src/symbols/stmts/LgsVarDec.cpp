#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"

void LgsVarDec::createIRStmt(LgsCodeGen* codeGen) {
    const auto IRType = type->getIRType(codeGen);
    const auto exprIRValue = expr->getIRValue(codeGen);
    if (shouldAllocate(IRType)) {
        IRValue = codeGen->builder.CreateAlloca(IRType);
        codeGen->builder.CreateStore(exprIRValue, IRValue);
    } else {
        IRValue = exprIRValue;
    }
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->asMap() || type->asDArray() || expr->asInstance()) return false;
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
}

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}
