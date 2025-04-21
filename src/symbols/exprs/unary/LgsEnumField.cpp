#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::getGEP(CodeGenMetadata* metadata, Value* instance) {
    return createIRStr(metadata->module, name);
}
