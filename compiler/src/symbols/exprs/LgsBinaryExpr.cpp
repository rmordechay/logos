#include "exprs/LgsBinaryExpr.h"

#include "LgsType.h"
#include "codegen/LgsCgModule.h"
#include "LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsCgModule& cg) {
    return IRValue;
}

Value* LgsBinaryExpr::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

void LgsBinaryExpr::setDebugValue(LgsCgModule& cg) {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
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
