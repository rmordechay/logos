#include "types/LgsUnknownType.h"

string LgsUnknownType::prettyName() const {
    return name == "" ? typeName : name;
}

LgsExpr* LgsUnknownType::getZeroValue() {
    assert(0);
}

bool LgsUnknownType::equals(LgsType* other) {
    assert(0);
}

LgsType* LgsUnknownType::inferBinaryType(LgsType* other) {
    assert(0);
}

Type* LgsUnknownType::getIRType() {
    assert(0);
}

string LgsUnknownType::getIRName() {
    return name;
}