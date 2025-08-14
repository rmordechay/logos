#include "exprs/unary/LgsPrefixExpr.h"

std::string LgsPrefixExpr::prettyName() {
    assert(0);
}

Value* LgsPrefixExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto exprValue = expr->getIRValue(codeGen);
    switch (op) {
    case NOT_PREFIX: {
        return codeGen->builder.CreateNot(exprValue);
    }
    case MINUS_PREFIX:
        const auto zero = ConstantInt::get(type->getIRType(codeGen), 0);
        return codeGen->builder.CreateSub(zero, exprValue);
    }
    assert(false);
}
