#include "exprs/LgsBinaryExpr.h"

#include <assert.h>

void LgsBinaryExpr::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

bool LgsBinaryExpr::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsBinaryExpr::asText() {
    return left->asText() + ' ' + op.text + ' ' + right->asText();
}

LgsExpr* LgsBinaryExpr::clone() {
    const auto newBinaryExpr = new LgsBinaryExpr(*this);
    newBinaryExpr->left = left->clone();
    newBinaryExpr->right = right->clone();
    return newBinaryExpr;
}

LgsBinaryExpr::~LgsBinaryExpr() {
    freeExpr(left);
    freeExpr(right);
    left = nullptr;
    right = nullptr;
}
