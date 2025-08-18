#include "exprs/unary/LgsPostfixExpr.h"
#include "LgsType.h"

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

void LgsPostfixExpr::createIRValue(LgsCodeGen* codeGen) {
    IRValue = IncOrDecValue(codeGen);
}

std::string LgsPostfixExpr::pname() {
    assert(0);
}

json::value_ref LgsPostfixExpr::asJSON() {
    json::object obj;
    return obj;
}

LgsPostfixExpr::~LgsPostfixExpr() {
    if (expr) {
        delete expr;
        expr = nullptr;
    }
}
