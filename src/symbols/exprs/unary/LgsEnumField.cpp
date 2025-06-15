#include "exprs/unary/LgsEnumField.h"
#include "utils/LgsUtils.h"

Value* LgsEnumField::createIRValue(LgsRuntime* runtime) {
    return getIRStr(runtime, name);
}
