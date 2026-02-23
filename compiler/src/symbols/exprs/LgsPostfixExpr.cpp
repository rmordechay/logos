#include "exprs/LgsPostfixExpr.h"

#include <assert.h>

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
