#include "stmts/LgsAssignment.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsBinaryExpr.h"

void LgsAssignment::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsAssignment::~LgsAssignment() {
    freeExpr(binaryExpr);
    freeExpr(left);
    freeExpr(right);
    binaryExpr = nullptr;
    left = nullptr;
    right = nullptr;
}
