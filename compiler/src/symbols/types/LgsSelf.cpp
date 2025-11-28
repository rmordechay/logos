#include "types/LgsSelf.h"

Type* LgsSelf::getIRType(LgsCgModule& cg) {
    assert(0);
}

Constant* LgsSelf::getRTType(LgsCgModule& cg) {
    assert(0);
}

size_t LgsSelf::sizeBytes() {
    assert(0);
}

LgsExpr* LgsSelf::getZeroValue() {
    return baseType->getZeroValue();
}

std::string LgsSelf::getName() {
    return name;
}

bool LgsSelf::canCastTo(LgsType* other) {
    assert(0);
}

std::string LgsSelf::strFormatPart() const {
    assert(0);
}

llvm::DIType* LgsSelf::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsSelf::clone() {
    assert(0);
}
