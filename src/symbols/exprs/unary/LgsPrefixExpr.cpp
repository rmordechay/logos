#include "exprs/unary/LgsPrefixExpr.h"

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
        IRValue = codeGen->callSqrt(exprIRVal);
        break;
    }
    }
}

json::value_ref LgsPrefixExpr::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsPrefixExpr::pname() {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    if (expr) {
        delete expr;
        expr = nullptr;
    }
}
