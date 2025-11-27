#include "exprs/LgsPrefixExpr.h"

#include "LgsUtils.h"

Value* LgsPrefixExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsPrefixExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

std::string LgsPrefixExpr::asText() {
    assert(0);
}

LgsPrefixExpr::~LgsPrefixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
