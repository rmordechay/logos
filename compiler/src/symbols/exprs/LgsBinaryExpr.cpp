#include "exprs/LgsBinaryExpr.h"

void LgsBinaryExpr::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

bool LgsBinaryExpr::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsBinaryExpr::asText() {
    return left->asText() + ' ' + op.text + ' ' + right->asText();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    freeExpr(left);
    freeExpr(right);
    left = nullptr;
    right = nullptr;
}
