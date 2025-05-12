#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::getGEP(CodeGenMetadata* metadata, Value* instance) {
    return getIRStr(metadata->module, name);
}
