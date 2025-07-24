#include "types/LgsPtr.h"
#include "exprs/LgsNullValue.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

string LgsPtr::getName() {
    return name;
}

string LgsPtr::prettyName() {
    return name;
}

Type* LgsPtr::getIRType(LgsModule* module) {
    return ptrTy(module);
}

size_t LgsPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    return new LgsNullValue();
}

bool LgsPtr::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}
