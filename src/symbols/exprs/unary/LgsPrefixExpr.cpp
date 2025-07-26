#include "exprs/unary/LgsPrefixExpr.h"

string LgsPrefixExpr::prettyName() {
    assert(0);
}

Value* LgsPrefixExpr::createIRValue(LgsModule* module) {
    const auto exprValue = expr->getIRValue(module);
    switch (op) {
    case NOT_PREFIX: {
        return module->builder.CreateNot(exprValue);
    }
    case MINUS_PREFIX:
        const auto zero = ConstantInt::get(type->getIRType(module), 0);
        return module->builder.CreateSub(zero, exprValue);
    }
    assert(false);
}
