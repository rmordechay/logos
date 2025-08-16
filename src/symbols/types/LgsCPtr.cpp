#include "types/LgsCPtr.h"
#include "exprs/LgsNull.h"
#include "types/LgsAny.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"
#include "types/primitives/LgsLong.h"

std::string LgsCPtr::getName() {
    return name;
}

std::string LgsCPtr::pname() {
    return name;
}

Type* LgsCPtr::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

size_t LgsCPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsCPtr::getZeroValue() {
    return new LgsNull();
}

bool LgsCPtr::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsSArray::name) return true;
    if (IRName == LgsDArray::name) return true;
    return name == IRName;
}
