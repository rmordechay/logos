#include "types/primitives/LgsLong.h"


#include "logos/LgsRuntime.h"

string LgsLong::prettyName() const {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    assert(false);
}

Type* LgsLong::getIRType(LgsRuntime* runtime) {
    return runtime->builder.getInt64Ty();
}

LgsExpr* LgsLong::getZeroValue() {
    assert(false);
}

LgsType* LgsLong::inferBinaryType(LgsType* other) {
    assert(false);
}

string LgsLong::getIRName() {
    return name;
}
