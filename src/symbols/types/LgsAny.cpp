#include "types/LgsAny.h"

#include "codegen/CodegenMetadata.h"
#include "logos/LgsRuntime.h"

size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsRuntime* runtime) {
    return runtime->builder.getPtrTy();
}

string LgsAny::getIRName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(false);
}

string LgsAny::prettyName() const {
    return name;
}

bool LgsAny::equals(LgsType* other) {
    // TODO should everything equals Any?
    return true;
}

LgsType* LgsAny::inferBinaryType(LgsType* other) {
    assert(false);
}
