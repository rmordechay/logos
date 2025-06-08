#include "exprs/LgsCast.h"


class LgsRuntime;

Value* LgsCast::createIRValue(LgsRuntime* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return toValue->addIR(runtime, other);
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
