#include "exprs/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsRuntime* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return toValue->addIR(runtime, other);
}

std::string LgsCast::pName() {
    return fromValue->pName() + "->" + toType->pName();
}

LgsCast::~LgsCast() {
    delete fromValue;
    if (toValue) {
        delete toValue;
    }
}
