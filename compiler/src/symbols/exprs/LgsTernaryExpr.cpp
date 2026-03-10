#include "exprs/LgsTernaryExpr.h"

#include <assert.h>

#include "exprs/LgsExpr.h"

std::string LgsTernaryExpr::asText() {
    assert(0);
}

void LgsTernaryExpr::setDebugValue(LgsCodeGen& cg) {
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
