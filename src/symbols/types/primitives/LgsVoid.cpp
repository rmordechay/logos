#include "types/primitives/LgsVoid.h"

#include "exprs/LgsNull.h"


string LgsVoid::prettyName() const {
    return name;
}

Type* LgsVoid::getIRType() {
    return Type::getVoidTy(context);
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

bool LgsVoid::equals(LgsType* other) {
    return name == other->getIRName();
}
