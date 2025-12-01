#include "exprs/LgsBinaryExpr.h"

#include "codegen/LgsCgModule.h"

Value* LgsBinaryExpr::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsBinaryExpr::setDebugValue(LgsCgModule& cg) {
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
    freeExpr(results);
    left = nullptr;
    right = nullptr;
    results = nullptr;
}
