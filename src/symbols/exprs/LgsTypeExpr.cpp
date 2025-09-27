#include "exprs/LgsTypeExpr.h"

#include "LgsType.h"

json::value LgsTypeExpr::asJsonStr() {
    assert(0);
}

std::string LgsTypeExpr::getName() {
    return type->pname();
}
