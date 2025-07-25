#include "types/LgsCPtr.h"
#include "exprs/LgsNullValue.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

string LgsCPtr::getName() {
    return name;
}

string LgsCPtr::prettyName() {
    return name;
}

Type* LgsCPtr::getIRType(LgsModule* module) {
    return ptrTy(module);
}

size_t LgsCPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsCPtr::getZeroValue() {
    return new LgsNullValue();
}

bool LgsCPtr::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}
