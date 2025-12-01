#include "exprs/LgsTernaryExpr.h"

std::string LgsTernaryExpr::asText() {
    assert(0);
}

void LgsTernaryExpr::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsTernaryExpr::~LgsTernaryExpr() {
    freeExpr(condExpr);
    freeExpr(thenExpr);
    freeExpr(elseExpr);
    condExpr = nullptr;
    thenExpr = nullptr;
    elseExpr = nullptr;
}
