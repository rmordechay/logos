#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"

void LgsVarDec::createIRStmt(LgsModule* module) {
    const auto IRType = type->getIRType(module);
    auto exprIRValue = expr->getIRValue(module);
    if (shouldLoadIRArg(exprIRValue, expr)) {
        exprIRValue = module->builder.CreateLoad(IRType, exprIRValue);
    }
    if (shouldAllocate(IRType)) {
        IRValue = module->builder.CreateAlloca(IRType);
        module->builder.CreateStore(exprIRValue, IRValue);
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
