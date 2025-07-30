#include "../../../../include/symbols/exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsCodeGen* codeGen) {
    return toValue->getIRValue(codeGen);
}

Value* LgsCast::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return toValue->addIR(codeGen, other);
}

std::string LgsCast::prettyName() {
    return fromValue->prettyName() + "->" + toType->prettyName();
}

LgsCast::~LgsCast() {
    delete fromValue;
    if (toValue) {
        delete toValue;
    }
}
