#include "exprs/LgsPrefixExpr.h"

#include "LgsUtils.h"

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
