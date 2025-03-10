#include "unary/constants/LogosConstant.h"
#include "unary/constants/LogosStringConst.h"
#include <LogosMetadata.h>
#include <types/LogosString.h>

struct CodeGenMetadata;

Value* LogosConstant::computeIRValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder.getInt32(*intValue);
    }
    if (const auto stringValue = get_if<LogosStringConst*>(&value)) {
        auto value = (*stringValue)->value;
        value.erase(0, 1);
        value.erase(value.size() - 1);
        const auto irString = ConstantDataArray::getString(context, value, true);
        // TODO check if already exists
        return new GlobalVariable(*metadata->currentModule, irString->getType(), true, GlobalValue::PrivateLinkage, irString, ".str");
    }
    return nullptr;
}
