#include "types/LgsGroup.h"



Type* LgsGroup::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
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

size_t LgsGroup::getSizeBytes() {
    assert(0);
}

bool LgsGroup::equals(LgsType* other) {
    for (const auto type : types) {
        if (type->equals(other)) return true;
    }
    return false;
}
