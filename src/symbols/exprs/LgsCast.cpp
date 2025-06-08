#include "exprs/LgsCast.h"
#include "types/LgsType.h"

Value* LgsCast::createIRValue(LgsRuntime* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return toValue->addIR(runtime, other);
}

LgsCast::~LgsCast() {
    delete toType;
    delete fromValue;
    if (toValue) {
        delete toValue;
    }
}
