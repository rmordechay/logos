#include "stmts/LgsAssignment.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsVariable.h"
#include "LgsUtils.h"

void LgsAssignment::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsAssignment::~LgsAssignment() {
    freeExpr(lValue);
    freeExpr(rValue);
    lValue = nullptr;
    rValue = nullptr;
}
