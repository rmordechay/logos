#include "exprs/LgsCast.h"

Value* LgsCast::createIRValue(CodeGenMetadata* metadata) {
    return toValue->getIRValue(metadata);
}

Value* LgsCast::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    return toValue->addIR(metadata, other);
}

bool LgsCast::cast() {
    if (const auto v = fromValue->castStatically(toType)) {
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
