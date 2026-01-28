#include "exprs/LgsPostfixExpr.h"
#include "LgsType.h"
#include "LgsUtils.h"

std::string LgsPostfixExpr::asText() {
    assert(0);
}

void LgsPostfixExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsPostfixExpr::~LgsPostfixExpr() {
    freeExpr(baseExpr);
    baseExpr = nullptr;
}
