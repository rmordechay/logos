#include "exprs/unary/LgsEnumField.h"

Value* LgsEnumField::getGEP(CodegenMetadata* metadata, Value* instance) {
    return getIRStr(metadata->module, name);
}
