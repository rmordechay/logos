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
    return baseType->equals(other);
}

size_t LgsNullable::getSizeBytes() {
    return 0;
}

LgsNullable::~LgsNullable() {
    freeType(baseType);
}
