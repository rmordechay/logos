#include "exprs/LgsBinaryExpr.h"
#include "utils/LgsUtils.h"

json::value LgsBinaryExpr::asJSON() {
    assert(0);
}

std::string LgsBinaryExpr::pname() {
    return left->pname() + ' ' + opStr + ' ' + right->pname();
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
