#include "../../../../include/symbols/exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

void LgsCast::createIRValue(LgsCodeGen* codeGen) {
    IRValue = toValue->getIRValue(codeGen);
}

Value* LgsCast::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return toValue->addIR(codeGen, other);
}

std::string LgsCast::prettyName() {
    return fromValue->prettyName() + "->" + toType->prettyName();
}

LgsCast::~LgsCast() {
    if (fromValue) {
        delete fromValue;
        fromValue = nullptr;
    }
    if (toValue) {
        delete toValue;
        toValue = nullptr;
    }
    if (toType) {
        freeType(toType);
        toType = nullptr;
    }
}
