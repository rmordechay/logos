#include "exprs/LgsCast.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsRuntime* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return toValue->addIR(runtime, other);
}

LgsCast::~LgsCast() {
    freeType(toType);
    delete fromValue;
    if (toValue) {
        delete toValue;
    }
}
