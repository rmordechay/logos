#include "exprs/LgsBinaryExpr.h"

#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"
#include "LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsBinaryExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

void LgsBinaryExpr::setDebugValue(LgsLLVMGen& cg) {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
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
    if (type) newBinaryExpr->type = type->clone();
    if (results) newBinaryExpr->results = results->clone();
    return newBinaryExpr;
}

LgsBinaryExpr::~LgsBinaryExpr() {
    freeExpr(left);
    freeExpr(right);
    freeExpr(results);
    left = nullptr;
    right = nullptr;
    results = nullptr;
}
