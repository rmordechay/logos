#include "exprs/LogosConstant.h"

string LogosConstant::getName() {
    return "";
}

LogosSymbolType LogosConstant::getSymbolType() {
    return CONSTANT;
}

Value* LogosConstant::computeIRValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder->getInt32(*intValue);
    }
    return nullptr;
}