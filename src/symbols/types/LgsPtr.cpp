#include "types/LgsPtr.h"

#include "exprs/LgsNullableExpr.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsLong.h"

std::string LgsPtr::getName() {
    return name;
}

json::value LgsPtr::asJsonStr() {
    assert(0);
}

std::string LgsPtr::pname() {
    return name;
}

Type* LgsPtr::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

size_t LgsPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    return new LgsNullableExpr();
}

Lgs_RTType LgsPtr::getRTType() {
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
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
