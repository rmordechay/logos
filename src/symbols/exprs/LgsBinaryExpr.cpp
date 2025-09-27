#include "exprs/LgsBinaryExpr.h"
#include "utils/LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

json::value LgsBinaryExpr::asJsonStr() {
    assert(0);
}

std::string LgsBinaryExpr::getName() {
    return left->getName() + ' ' + opStr + ' ' + right->getName();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    if (left) {
        freeExpr(left);
        right = nullptr;
    }
    if (right) {
        freeExpr(right);
        left = nullptr;
    }
}
