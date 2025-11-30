#include "exprs/LgsPrefixExpr.h"

#include "LgsUtils.h"

Value* LgsPrefixExpr::loadIR(LgsCgModule& cg) {
    return IRValue;
}

std::string LgsPrefixExpr::asText() {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
