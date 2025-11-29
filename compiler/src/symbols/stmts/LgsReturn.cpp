#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
