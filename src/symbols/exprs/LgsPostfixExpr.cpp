#include "exprs/LgsPostfixExpr.h"
#include "LgsType.h"
#include "utils/LgsUtils.h"

std::string LgsPostfixExpr::asText() {
    assert(0);
}

LgsPostfixExpr::~LgsPostfixExpr() {
    freeExpr(baseExpr);
    baseExpr = nullptr;
}
