#include "exprs/LgsPrefixExpr.h"

#include "LgsUtils.h"

Value* LgsPrefixExpr::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

std::string LgsPrefixExpr::asText() {
    assert(0);
}

void LgsPrefixExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
