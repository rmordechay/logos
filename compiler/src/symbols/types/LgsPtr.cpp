#include "types/LgsPtr.h"

#include "exprs/LgsNull.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsLong.h"
#include "LgsUtils.h"

std::string LgsPtr::getName() {
    return name;
}

std::string LgsPtr::pname() {
    return name;
}

Type* LgsPtr::getIRType(LgsCgModule& cg) {
    return cg.ptrTy();
}

Constant* LgsPtr::getRTType(LgsCgModule& cg) {
    assert(0);
}

size_t LgsPtr::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    return new LgsNull();
}

bool LgsPtr::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsSArray::name) return true;
    if (IRName == LgsDArray::name) return true;
    return name == IRName;
}

std::string LgsPtr::strFormatPart() const {
    return baseType->strFormatPart();
}

llvm::DIType* LgsPtr::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsPtr::clone() {
    assert(0);
}

LgsPtr::~LgsPtr() {
    freeType(baseType);
    baseType = nullptr;
}
