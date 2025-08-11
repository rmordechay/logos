#include "types/LgsNullable.h"
#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
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

size_t LgsNullable::getSizeBytes() {
    return 0;
}

LgsNullable::~LgsNullable() {
    freeType(baseType);
}
