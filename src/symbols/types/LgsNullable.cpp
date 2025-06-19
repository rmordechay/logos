#include "types/LgsNullable.h"

#include "logos/LgsRuntime.h"

Type* LgsNullable::getIRType() {
    return PointerType::getUnqual(context);
}

string LgsNullable::getIRName() {
    assert(0);
}

LgsExpr* LgsNullable::getZeroValue() {
    return baseType->getZeroValue();
}

string LgsNullable::prettyName() const {
    return baseType->prettyName() + '?';
}

bool LgsNullable::equals(LgsType* other) {
    assert(0);
}
