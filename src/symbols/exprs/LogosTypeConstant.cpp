#include "exprs/LogosTypeConstant.h"

string LogosTypeConstant::getName() {
    return type->getName();
}

Value* LogosTypeConstant::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}
