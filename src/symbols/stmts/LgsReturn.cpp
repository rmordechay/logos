#include "stmts/LgsReturn.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

json::value LgsReturn::asJsonStr() {
    json::object obj;
    obj["expr"] = expr->asJsonStr();
    return obj;
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
