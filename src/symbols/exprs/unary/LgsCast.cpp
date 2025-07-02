#include "../../../../include/symbols/exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsModule* module) {
    return toValue->getIRValue(module);
}

Value* LgsCast::addIR(LgsModule* module, LgsExpr* other) {
    return toValue->addIR(module, other);
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
