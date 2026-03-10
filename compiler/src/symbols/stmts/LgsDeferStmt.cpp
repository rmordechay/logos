#include "stmts/LgsDeferStmt.h"

#include <exprs/LgsSelection.h>
#include <assert.h>

#include "exprs/LgsExpr.h"

class LgsFuncCall;

void LgsDeferStmt::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsFuncCall* LgsDeferStmt::getAsFuncCall() const {
    if (const auto selection = expr->asSelection()) return selection->asMethodCall();
    return expr->asFuncCall();
}

LgsDeferStmt::~LgsDeferStmt() {
    freeExpr(expr);
    expr = nullptr;
}
