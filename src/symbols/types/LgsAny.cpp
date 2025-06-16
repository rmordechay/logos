#include "types/LgsAny.h"

#include "logos/LgsRuntime.h"


size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType() {
    return PointerType::getUnqual(context);
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