#include "exprs/unary/LgsPrefixExpr.h"

Value* LgsPrefixExpr::createIRValue(LgsRuntime* runtime) {
    const auto exprValue = expr->getIRValue(runtime);
    switch (op) {
    case NOT_PREFIX: {
        return runtime->builder.CreateNot(exprValue);
    }
    case MINUS_PREFIX:
        const auto zero = ConstantInt::get(type->getIRType(), 0);
        return runtime->builder.CreateSub(zero, exprValue);
    }
    assert(false);
}