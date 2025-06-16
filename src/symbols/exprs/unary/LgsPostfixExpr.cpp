#include "exprs/unary/LgsPostfixExpr.h"

#include "../../../../include/symbols/LgsType.h"

Value* LgsPostfixExpr::createIRValue(LgsRuntime* runtime) {
    return IncOrDecValue(runtime);
}

void LgsPostfixExpr::createIRStmt(LgsRuntime* runtime) {
    IncOrDecValue(runtime);
}

Value* LgsPostfixExpr::IncOrDecValue(LgsRuntime* runtime) const {
    const auto exprIRValue = expr->createIRValue(runtime);
    const auto exprIRType = expr->type->getIRType();
    const auto exprLoad = runtime->builder.CreateLoad(exprIRType, exprIRValue);
    const auto oneConst = ConstantInt::get(exprIRType, 1);
    Value* updatedValue = nullptr;
    switch (op) {
    case INC:
        updatedValue = runtime->builder.CreateAdd(exprLoad, oneConst);
        break;
    case DEC:
        updatedValue = runtime->builder.CreateSub(exprLoad, oneConst);
        break;
    }
    runtime->builder.CreateStore(updatedValue, exprIRValue);
    return updatedValue;
}
