#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::getIRValue(CodeGenMetadata* metadata) {
    return createIRStr(metadata->module, name);
}
