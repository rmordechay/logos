#include "stmts/LgsDeferStmt.h"

#include <exprs/LgsFuncCall.h>
#include <exprs/LgsSelection.h>

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
