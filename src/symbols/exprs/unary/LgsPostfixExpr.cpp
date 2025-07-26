#include "exprs/unary/LgsPostfixExpr.h"

#include "../../../../include/symbols/LgsType.h"

Value* LgsPostfixExpr::createIRValue(LgsModule* module) {
    return IncOrDecValue(module);
}

string LgsPostfixExpr::prettyName() {
    assert(0);
}

void LgsPostfixExpr::createIRStmt(LgsModule* module) {
    IncOrDecValue(module);
}

Value* LgsPostfixExpr::IncOrDecValue(LgsModule* module) const {
    const auto exprIRValue = expr->getIRValue(module);
    const auto exprIRType = expr->type->getIRType(module);
    const auto exprLoad = module->builder.CreateLoad(exprIRType, exprIRValue);
    const auto oneConst = ConstantInt::get(exprIRType, 1);
    Value* updatedValue = nullptr;
    switch (op) {
    case INC:
        updatedValue = module->builder.CreateAdd(exprLoad, oneConst);
        break;
    case DEC:
        updatedValue = module->builder.CreateSub(exprLoad, oneConst);
        break;
    }
    module->builder.CreateStore(updatedValue, exprIRValue);
    return updatedValue;
}
