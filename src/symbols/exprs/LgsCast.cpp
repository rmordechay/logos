#include "exprs/LgsCast.h"
#include "types/LgsType.h"

Value* LgsCast::createIRValue(CodegenMetadata* metadata) {
    return toValue->getIRValue(metadata);
}

Value* LgsCast::addIR(CodegenMetadata* metadata, LgsExpr* other) {
    return toValue->addIR(metadata, other);
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
