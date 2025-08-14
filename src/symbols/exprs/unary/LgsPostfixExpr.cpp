#include "exprs/unary/LgsPostfixExpr.h"

#include "../../../../include/symbols/LgsType.h"

Value* LgsPostfixExpr::createIRValue(LgsCodeGen* codeGen) {
    return IncOrDecValue(codeGen);
}

std::string LgsPostfixExpr::prettyName() {
    assert(0);
}

void LgsPostfixExpr::createIRStmt(LgsCodeGen* codeGen) {
    IncOrDecValue(codeGen);
}

Value* LgsPostfixExpr::IncOrDecValue(LgsCodeGen* codeGen) const {
    const auto exprIRValue = expr->getIRValue(codeGen);
    const auto exprIRType = expr->type->getIRType(codeGen);
    const auto exprLoad = codeGen->builder.CreateLoad(exprIRType, exprIRValue);
    const auto oneConst = ConstantInt::get(exprIRType, 1);
    Value* updatedValue = nullptr;
    switch (op) {
    case INC:
        updatedValue = codeGen->builder.CreateAdd(exprLoad, oneConst);
        break;
    case DEC:
        updatedValue = codeGen->builder.CreateSub(exprLoad, oneConst);
        break;
    }
    codeGen->builder.CreateStore(updatedValue, exprIRValue);
    return updatedValue;
}
