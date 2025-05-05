#include "types/LgsVoid.h"

#include "exprs/LgsNull.h"


const std::string LgsVoid::getPrettyName() const {
    return name;
}

bool LgsVoid::isVoid() {
    return true;
}

Type* LgsVoid::getIRType() {
    return voidTy;
}

LgsExpr* LgsVoid::getZeroValue() {
    return new LgsNull();
}

LgsType* LgsVoid::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsVoid::equals(LgsType* other) const {
    return name == other->getPrettyName();
}
