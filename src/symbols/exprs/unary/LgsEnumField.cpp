#include "exprs/unary/LgsEnumField.h"

#include "utils/LgsUtils.h"

Value* LgsEnumField::getGEP(Module* module, Value* instance) {
    return getIRStr(module, name);
}
