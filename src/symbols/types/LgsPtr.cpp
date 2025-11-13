#include "types/LgsPtr.h"

#include "exprs/LgsNull.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsLong.h"
#include "utils/LgsUtils.h"

std::string LgsPtr::getName() {
    return name;
}

std::string LgsPtr::pname() {
    return name;
}

Type* LgsPtr::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

size_t LgsPtr::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    return new LgsNull();
}

Lgs_TypeKind LgsPtr::getRTTypeKind() {
    assert(0);
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

LgsPtr::~LgsPtr() {
    freeType(baseType);
    baseType = nullptr;
}
