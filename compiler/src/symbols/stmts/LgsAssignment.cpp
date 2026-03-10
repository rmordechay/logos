#include "stmts/LgsAssignment.h"

#include <assert.h>

#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsExpr.h"

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
