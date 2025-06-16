#include "exprs/unary/LgsPrefixExpr.h"

Value* LgsPrefixExpr::createIRValue(LgsRuntime* runtime) {
    switch (op) {
    case NOT_PREFIX:
        return runtime->builder.CreateNot(expr->getIRValue(runtime));
    case MINUS_PREFIX:
        break;
    }
    assert(false);
}