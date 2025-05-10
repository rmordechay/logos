#include "types/LgsUnknownType.h"

string LgsUnknownType::prettyName() const {
    return name == "" ? typeName : name;
}

LgsExpr* LgsUnknownType::getZeroValue() {
    assert(false);
}

bool LgsUnknownType::equals(LgsType* other) {
    assert(false);
}

LgsType* LgsUnknownType::inferBinaryType(LgsType* other) {
    assert(false);
}

Type* LgsUnknownType::getIRType() {
    assert(false);
}

string LgsUnknownType::getIRName() {
    return name;
}