#include "types/LgsGroup.h"

Type* LgsGroup::getIRType(LgsModule* module) {
    return ptrTy(module);
}

LgsExpr* LgsGroup::getZeroValue() {
    assert(0);
}

string LgsGroup::getName() {
    return name;
}

string LgsGroup::prettyName() {
    return name;
}

bool LgsGroup::equals(LgsType* other) {
    for (const auto type : types) {
        if (type->equals(other)) return true;
    }
    return false;
}