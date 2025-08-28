#include "exprs/unary/LgsTypeExpr.h"

#include "LgsType.h"

json::value LgsTypeExpr::asJSON() {
    assert(0);
}

std::string LgsTypeExpr::pname() {
    return type->pname();
}
