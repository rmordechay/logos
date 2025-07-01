#include "types/LgsAny.h"

#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"


size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LLVMContext& context) {
    return ptrTy(context);
}

string LgsAny::getIRName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

string LgsAny::prettyName() const {
    return name;
}

bool LgsAny::equals(LgsType* other) {
    return true;
}