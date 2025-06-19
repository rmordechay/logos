#include "types/primitives/LgsVoid.h"

#include "exprs/LgsNull.h"


string LgsVoid::prettyName() const {
    return name;
}

Type* LgsVoid::getIRType() {
    return Type::getVoidTy(context);
}

size_t LgsVoid::getSizeBytes() {
    return 0;
}

string LgsVoid::getIRName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return nullptr;
}

bool LgsVoid::equals(LgsType* other) {
    return name == other->getIRName();
}
