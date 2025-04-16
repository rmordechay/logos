#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::createIRValue(CodeGenMetadata* metadata) {
    return createIRStr(metadata->module, name);
}
