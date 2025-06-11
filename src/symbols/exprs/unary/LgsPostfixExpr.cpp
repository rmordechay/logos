#include "exprs/unary/LgsPostfixExpr.h"

#include "types/LgsType.h"

Value* LgsPostfixExpr::createIRValue(LgsRuntime* runtime) {
    return IncOrDec(runtime);
}

void LgsPostfixExpr::createIRStmt(LgsRuntime* runtime) {
    IncOrDec(runtime);
}

Value* LgsPostfixExpr::IncOrDec(LgsRuntime* runtime) const {
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
