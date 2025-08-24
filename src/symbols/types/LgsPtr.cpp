#include "types/LgsPtr.h"
#include "exprs/LgsNull.h"
#include "types/LgsAny.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"
#include "types/primitives/LgsLong.h"

std::string LgsPtr::getName() {
    return name;
}

json::value LgsPtr::asJSON() {
    assert(0);
}

std::string LgsPtr::pname() {
    return name;
}

Type* LgsPtr::getIRType(LgsLLVM& codeGen) {
    return codeGen.ptrTy();
}

size_t LgsPtr::getSizeBytes() {
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
    return "%p";
}

LgsPtr::~LgsPtr() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
