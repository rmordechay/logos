#include "exprs/unary/LgsEnumField.h"



Value* LgsEnumField::getGEP(LgsRuntime* runtime, Value* instance) {
    return getIRStr(runtime, name);
}
