#include "exprs/unary/LgsPrefixExpr.h"

std::string LgsPrefixExpr::pname() {
    assert(0);
}

void LgsPrefixExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto exprValue = expr->getIRValue(codeGen);
    switch (op) {
    case NOT_PREFIX: {
        IRValue = codeGen->builder.CreateNot(exprValue);
        break;
    }
    case MINUS_PREFIX: {
        const auto zero = ConstantInt::get(type->getIRType(codeGen), 0);
        IRValue = codeGen->builder.CreateSub(zero, exprValue);
        break;
    }
    case SQRT_PREFIX: {
        // IRValue = codeGen->callFunc("sqrt", FunctionType::get(), {exprValue});
        break;
    }
    }
    assert(false);
}
