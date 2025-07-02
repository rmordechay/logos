#include "exprs/unary/LgsEnumField.h"
#include "utils/LgsUtils.h"

Value* LgsEnumField::createIRValue(LgsModule* module) {
    return getIRStr(module, name);
}

string LgsEnumField::prettyName() {
    return name;
}
