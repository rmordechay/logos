#include "types/LgsAny.h"

#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"


size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsModule* module) {
    return ptrTy(module);
}

string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

string LgsAny::prettyName() {
    return name;
}

bool LgsAny::equals(LgsType* other) {
    return true;
}
