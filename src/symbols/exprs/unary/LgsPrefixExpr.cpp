#include "exprs/unary/LgsPrefixExpr.h"

#include "utils/LgsUtils.h"

json::value LgsPrefixExpr::asJSON() {
    assert(0);
}

std::string LgsPrefixExpr::pname() {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
