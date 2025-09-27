#include "exprs/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

std::string LgsCast::pname() {
    return fromValue->pname() + "->" + toType->pname();
}

json::value LgsCast::asJsonStr() {
    assert(0);
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeExpr(toValue);
    freeType(toType);
    fromValue = nullptr;
    toValue = nullptr;
    toType = nullptr;
}
