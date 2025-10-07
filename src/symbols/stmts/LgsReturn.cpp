#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
