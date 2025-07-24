#include "types/LgsUnknownType.h"

string LgsUnknownType::prettyName() {
    return getName();
}

string LgsUnknownType::getName() {
    return name == "" ? "<Unknown>" : name;
}

LgsExpr* LgsUnknownType::getZeroValue() {
    assert(0);
}

bool LgsUnknownType::equals(LgsType* other) {
    return false;
}

Type* LgsUnknownType::getIRType(LgsModule* module) {
    assert(0);
}