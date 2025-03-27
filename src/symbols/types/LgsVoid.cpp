#include "types/LgsVoid.h"

#include "exprs/LgsNull.h"


Type* LgsVoid::IRValue = Type::getVoidTy(context);

const std::string LgsVoid::getName() const {
    return name;
}

Type* LgsVoid::getIRType() {
    return IRValue;
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
