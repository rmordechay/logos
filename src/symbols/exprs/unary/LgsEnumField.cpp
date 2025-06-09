#include "exprs/unary/LgsEnumField.h"

#include "utils/LgsUtils.h"


Value* LgsEnumField::getGEP(LgsRuntime* runtime, Value* instance) {
    return getIRStr(runtime, name);
}
