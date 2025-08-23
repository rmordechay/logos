#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

json::value LgsReturn::asJSON() {
    json::object obj;
    obj["expr"] = expr->asJSON();
    return obj;
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
