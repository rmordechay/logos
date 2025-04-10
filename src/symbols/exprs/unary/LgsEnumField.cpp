#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::createIRValue(CodeGenMetadata* metadata) {
    return createGlobalStr(metadata->module, name);
}
