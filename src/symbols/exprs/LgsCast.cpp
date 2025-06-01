#include "exprs/LgsCast.h"
#include "types/LgsType.h"

Value* LgsCast::createIRValue(Module* module) {
    return toValue->getIRValue(module);
}

Value* LgsCast::addIR(Module* module, LgsExpr* other) {
    return toValue->addIR(module, other);
}

bool LgsCast::cast() {
    if (const auto v = fromValue->convertExpr(toType)) {
        toValue = v;
        return true;
    }
    return false;
}

LgsCast::~LgsCast() {
    delete toType;
    delete fromValue;
    if (toValue) {
        delete toValue;
    }
}
