#include "exprs/LgsPostfixExpr.h"
#include "LgsType.h"
#include "utils/LgsUtils.h"

std::string LgsPostfixExpr::pname() {
    assert(0);
}

json::value LgsPostfixExpr::asJsonStr() {
    assert(0);
}

LgsPostfixExpr::~LgsPostfixExpr() {
    freeExpr(expr);
    expr = nullptr;
}
