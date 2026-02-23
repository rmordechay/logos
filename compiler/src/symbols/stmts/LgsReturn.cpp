#include "stmts/LgsReturn.h"

#include "exprs/LgsExpr.h"

void LgsReturn::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

LgsStmt* LgsReturn::clone() {
    return new LgsReturn(expr->clone());
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
