#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

void LgsReturn::setDebugValue(LgsCgModule& cg) {
    setDebugLoc(cg);
}

LgsStmt* LgsReturn::clone() {
    const auto newReturn = new LgsReturn(*this);
    newReturn->expr = expr->clone();
    return newReturn;
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
