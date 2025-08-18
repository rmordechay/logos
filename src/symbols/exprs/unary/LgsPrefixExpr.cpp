#include "exprs/unary/LgsPrefixExpr.h"

std::string LgsPrefixExpr::pname() {
    assert(0);
}

void LgsPrefixExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto exprIRVal = expr->getIRValue(codeGen);
    switch (op) {
    case NOT_PREFIX: {
        IRValue = codeGen->builder.CreateNot(exprIRVal);
        break;
    }
    case MINUS_PREFIX: {
        const auto zero = ConstantInt::get(type->getIRType(codeGen), 0);
        IRValue = codeGen->builder.CreateSub(zero, exprIRVal);
        break;
    }
    case SQRT_PREFIX: {
        const auto ft = FunctionType::get(codeGen->doubleTy(), {codeGen->doubleTy()}, false);
        const auto d = codeGen->builder.CreateSIToFP(exprIRVal, codeGen->doubleTy());
        IRValue = codeGen->callFunc("sqrt", ft, {d});
        break;
    }
    }
}
