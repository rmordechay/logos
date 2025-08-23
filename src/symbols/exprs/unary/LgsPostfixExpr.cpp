#include "exprs/unary/LgsPostfixExpr.h"
#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsPostfixExpr::IncOrDecValue(LgsCodeGen& codeGen) const {
    const auto exprIRValue = expr->IRValue;
    const auto exprIRType = expr->type->getIRType(codeGen);
    const auto exprLoad = codeGen.builder.CreateLoad(exprIRType, exprIRValue);
    const auto oneConst = ConstantInt::get(exprIRType, 1);
    Value* updatedValue = nullptr;
    switch (op) {
    case INC:
        updatedValue = codeGen.builder.CreateAdd(exprLoad, oneConst);
        break;
    case DEC:
        updatedValue = codeGen.builder.CreateSub(exprLoad, oneConst);
        break;
    }
    codeGen.builder.CreateStore(updatedValue, exprIRValue);
    return updatedValue;
}

std::string LgsPostfixExpr::pname() {
    assert(0);
}

json::value LgsPostfixExpr::asJSON() {
    assert(0);
}

LgsPostfixExpr::~LgsPostfixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
