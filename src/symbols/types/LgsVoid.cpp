#include "types/LgsVoid.h"

#include "exprs/LgsNull.h"

const std::string LgsVoid::getName() const {
    return name;
}

Type* LgsVoid::getIRType() {
    return Type::getVoidTy(context);
}

LgsExpr* LgsVoid::getZeroValue() {
    return new LgsNull();
}

LgsType* LgsVoid::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsVoid::equals(LgsType* other) const {
    return name == other->getName();
}