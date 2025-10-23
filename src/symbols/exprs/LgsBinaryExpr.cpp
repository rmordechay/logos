#include "exprs/LgsBinaryExpr.h"
#include "utils/LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsBinaryExpr::asText() {
    return left->asText() + ' ' + op.name + ' ' + right->asText();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    freeExpr(left);
    freeExpr(right);
    freeExpr(results);
    left = nullptr;
    right = nullptr;
    results = nullptr;
}
