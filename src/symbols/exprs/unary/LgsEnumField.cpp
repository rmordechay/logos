#include "exprs/unary/LgsEnumField.h"
#include "utils/LgsUtils.h"

Value* LgsEnumField::createIRValue(LgsModule* runtime) {
    return getIRStr(runtime, name);
}

string LgsEnumField::prettyName() {
    return name;
}
