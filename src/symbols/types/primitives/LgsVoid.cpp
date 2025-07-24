#include "types/primitives/LgsVoid.h"

#include "exprs/LgsNullValue.h"


string LgsVoid::prettyName() {
    return name;
}

Type* LgsVoid::getIRType(LgsModule* module) {
    return Type::getVoidTy(module->context);
}

size_t LgsVoid::getSizeBytes() {
    return 0;
}

string LgsVoid::getName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return nullptr;
}

bool LgsVoid::equals(LgsType* other) {
    return name == other->getName();
}
