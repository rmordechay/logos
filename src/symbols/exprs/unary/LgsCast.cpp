#include "../../../../include/symbols/exprs/unary/LgsCast.h"

#include "LgsType.h"
#include "utils/LgsUtils.h"

Value* LgsCast::createIRValue(LgsModule* runtime) {
    return toValue->getIRValue(runtime);
}

Value* LgsCast::addIR(LgsModule* runtime, LgsExpr* other) {
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
