#include "types/LgsUnknownType.h"

string LgsUnknownType::prettyName() const {
    return name == "" ? typeName : name;
}

LgsExpr* LgsUnknownType::getZeroValue() {
    assert(false);
}

bool LgsUnknownType::equals(LgsType* other) const {
    assert(false);
}

LgsType* LgsUnknownType::inferBinaryType(LgsType* other) {
    assert(false);
}

Type* LgsUnknownType::getIRType() {
    assert(false);
}

string LgsUnknownType::getIRName() {
    assert(false);
}