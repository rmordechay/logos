#include "exprs/LogosConstant.h"

#include <LogosMetadata.h>
#include <LogosSymbol.h>
#include <types/LogosInt.h>
#include <types/LogosString.h>


struct CodeGenMetadata;

Value* LogosConstant::computeIRValue(CodeGenMetadata* metadata) {
    if (dynamic_cast<LogosInt*>(type)) {
        return metadata->builder.getInt32(intVal);
    }
    if (dynamic_cast<LogosString*>(type)) {
        stringVal.erase(0, 1);
        stringVal.erase(stringVal.size() - 1);
        const auto irString = ConstantDataArray::getString(context, stringVal, true);
        return new GlobalVariable(*metadata->currentModule, irString->getType(), true, GlobalValue::PrivateLinkage, irString, ".str");
    }
    return nullptr;
}

void LogosConstant::setName(string name) {}

LogosSymbolType LogosConstant::getSymbolType() {
    return CONSTANT;
}

LogosConstant::~LogosConstant() {
}

string LogosConstant::getName() {
    return "";
}
