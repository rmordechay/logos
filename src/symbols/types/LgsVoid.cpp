#include "types/LgsVoid.h"

#include "exprs/LgsNull.h"


string LgsVoid::prettyName() const {
    return name;
}

bool LgsVoid::isVoid() {
    return true;
}

Type* LgsVoid::getIRType() {
    return voidTy;
}

string LgsVoid::getIRName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return new LgsNull();
}

LgsType* LgsVoid::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsVoid::equals(LgsType* other) const {
    return name == other->getIRName();
}
