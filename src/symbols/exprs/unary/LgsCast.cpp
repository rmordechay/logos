#include "../../../../include/symbols/exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsRuntime* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return toValue->addIR(runtime, other);
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
