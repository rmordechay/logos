#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "LgsUtils.h"

LgsStmt* LgsReturn::clone() {
    const auto newReturn = new LgsReturn(*this);
    newReturn->expr = expr->clone();
    return newReturn;
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
