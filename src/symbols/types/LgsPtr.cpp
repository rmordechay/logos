#include "types/LgsPtr.h"
#include "exprs/LgsNullValue.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

string LgsPtr::getIRName() {
    return name;
}

string LgsPtr::prettyName() const {
    return name;
}

Type* LgsPtr::getIRType(LLVMContext& context) {
    return ptrTy(context);
}

size_t LgsPtr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    return new LgsNullValue();
}

bool LgsPtr::equals(LgsType* other) {
    const auto IRName = other->getIRName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}
