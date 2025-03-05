#include "exprs/LogosConstant.h"

#include <LogosMetadata.h>
#include <LogosSymbol.h>
#include <types/LogosInt.h>
#include <types/LogosString.h>


struct CodeGenMetadata;

Value* LogosConstant::computeIRValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder.getInt32(*intValue);
    }
    if (const auto stringValue = get_if<string>(&value)) {
        stringValue->erase(0, 1);
        stringValue->erase(stringValue->size() - 1);
        const auto irString = ConstantDataArray::getString(context, *stringValue, true);
        return new GlobalVariable(*metadata->currentModule, irString->getType(), true, GlobalValue::PrivateLinkage, irString, ".str");
    }
    return nullptr;
}

void LogosConstant::setName(string name) {}

LogosSymbolType LogosConstant::getSymbolType() {
    return CONSTANT;
}

string LogosConstant::getName() {
    return "";
}
