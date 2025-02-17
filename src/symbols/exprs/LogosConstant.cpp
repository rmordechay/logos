#include "exprs/LogosConstant.h"

Value* LogosConstant::computeIRValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder->getInt32(*intValue);
    }
    return nullptr;
}

LogosSymbolType LogosConstant::getSymbolType() {
    return CONSTANT;
}

string LogosConstant::getName() {
    return "";
}
