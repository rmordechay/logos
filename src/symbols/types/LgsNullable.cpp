#include "types/LgsNullable.h"
#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LgsModule* module) {
    return ptrTy(module);
}

string LgsNullable::getName() {
    assert(0);
}

LgsExpr* LgsNullable::getZeroValue() {
    return baseType->getZeroValue();
}

string LgsNullable::prettyName() {
    return baseType->prettyName() + '?';
}

bool LgsNullable::equals(LgsType* other) {
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    return baseType->equals(otherNullable->baseType);
}
