#include "exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::addIR(LgsLLVM& codeGen, LgsExpr* other) {
    return toValue->addIR(codeGen, other);
}

std::string LgsCast::pname() {
    return fromValue->pname() + "->" + toType->pname();
}

json::value LgsCast::asJSON() {
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
