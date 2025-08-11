#include "../../../include/symbols/types/LgsVoid.h"

#include "exprs/LgsNull.h"


string LgsVoid::prettyName() {
    return name;
}

Type* LgsVoid::getIRType(LgsCodeGen* codeGen) {
    return Type::getVoidTy(codeGen->context);
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
