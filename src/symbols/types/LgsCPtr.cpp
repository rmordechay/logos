#include "types/LgsCPtr.h"
#include "exprs/LgsNull.h"
#include "types/LgsAny.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"
#include "types/primitives/LgsLong.h"

std::string LgsCPtr::getName() {
    return name;
}

json::value LgsCPtr::asJSON() {
    assert(0);
}

std::string LgsCPtr::pname() {
    return name;
}

Type* LgsCPtr::getIRType(LgsCodeGen& codeGen) {
    return codeGen.ptrTy();
}

size_t LgsCPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsCPtr::getZeroValue() {
    return new LgsNull();
}

bool LgsCPtr::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsSArray::name) return true;
    if (IRName == LgsDArray::name) return true;
    return name == IRName;
}

std::string LgsCPtr::strFormatPart() const {
    return "%p";
}

LgsCPtr::~LgsCPtr() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
