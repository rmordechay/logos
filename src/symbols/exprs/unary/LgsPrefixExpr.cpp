#include "exprs/unary/LgsPrefixExpr.h"

std::string LgsPrefixExpr::prettyName() {
    assert(0);
}

void LgsPrefixExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto exprValue = expr->getIRValue(codeGen);
    switch (op) {
    case NOT_PREFIX: {
        IRValue = codeGen->builder.CreateNot(exprValue);
        break;
    }
    case MINUS_PREFIX:
        const auto zero = ConstantInt::get(type->getIRType(codeGen), 0);
        IRValue = codeGen->builder.CreateSub(zero, exprValue);
        break;
    }
    assert(false);
}
