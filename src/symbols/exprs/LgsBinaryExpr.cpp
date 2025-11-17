#include "exprs/LgsBinaryExpr.h"

#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsBinaryExpr::asText() {
    return left->asText() + ' ' + op.text + ' ' + right->asText();
}

void LgsBinaryExpr::setDebugValue(LgsLLVMGen& cg) {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
}

bool LgsBinaryExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsExpr* LgsBinaryExpr::clone() {
    return new LgsBinaryExpr(left->clone(), right->clone(), op);
}

LgsBinaryExpr::~LgsBinaryExpr() {
    freeExpr(left);
    freeExpr(right);
    freeExpr(results);
    left = nullptr;
    right = nullptr;
    results = nullptr;
}
