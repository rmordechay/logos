#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

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
