#include "types/LgsGroup.h"



Type* LgsGroup::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

LgsExpr* LgsGroup::getZeroValue() {
    assert(0);
}

std::string LgsGroup::getName() {
    return name;
}

std::string LgsGroup::pname() {
    return name;
}

size_t LgsGroup::getSizeBytes() {
    assert(0);
}

std::string LgsGroup::strFormatPart() const {
    return "%s";
}

bool LgsGroup::equals(LgsType* other) {
    for (const auto type : types) {
        if (type->equals(other)) return true;
    }
    return false;
}
