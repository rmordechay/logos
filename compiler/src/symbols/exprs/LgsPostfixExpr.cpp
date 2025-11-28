#include "exprs/LgsPostfixExpr.h"
#include "LgsType.h"
#include "LgsUtils.h"

Value* LgsPostfixExpr::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

std::string LgsPostfixExpr::asText() {
    assert(0);
}

LgsPostfixExpr::~LgsPostfixExpr() {
    freeExpr(baseExpr);
    baseExpr = nullptr;
}
