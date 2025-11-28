#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "LgsUtils.h"

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
