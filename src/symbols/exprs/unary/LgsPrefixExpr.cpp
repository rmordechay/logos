#include "exprs/unary/LgsPrefixExpr.h"

Value* LgsPrefixExpr::createIRValue(LgsModule* module) {
    const auto exprValue = expr->getIRValue(module);
    switch (op) {
    case NOT_PREFIX: {
        return module->builder.CreateNot(exprValue);
    }
    case MINUS_PREFIX:
        const auto zero = ConstantInt::get(type->getIRType(module->context), 0);
        return module->builder.CreateSub(zero, exprValue);
    }
    assert(false);
}
