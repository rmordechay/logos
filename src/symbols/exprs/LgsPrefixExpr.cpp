#include "exprs/LgsPrefixExpr.h"

#include "utils/LgsUtils.h"

Value* LgsPrefixExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsPrefixExpr::pname() {
    assert(0);
}

json::value LgsPrefixExpr::asJSON() {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
