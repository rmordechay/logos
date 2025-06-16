#include "exprs/unary/LgsEnumField.h"
#include "utils/LgsUtils.h"

Value* LgsEnumField::createIRValue(LgsRuntime* runtime) {
    return getIRStr(runtime, name);
}

string LgsEnumField::pName() {
    return name;
}

uint32_t LgsDefaultEnumField::hashValue(LgsRuntime* runtime) {
    return hashedValue;
}
