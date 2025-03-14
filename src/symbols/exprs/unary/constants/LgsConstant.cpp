#include "constants/LgsConstant.h"
#include "constants/LgsStringConst.h"
#include <LogosMetadata.h>
#include <types/LgsString.h>

struct CodeGenMetadata;

Value* LgsConstant::createIRValue(CodeGenMetadata* metadata) {
    if (const auto intValue = get_if<int>(&value)) {
        return metadata->builder.getInt32(*intValue);
    }
    if (const auto stringValue = get_if<LgsStringConst*>(&value)) {
        auto str = (*stringValue)->value;
        str.erase(0, 1);
        str.erase(str.size() - 1);
        return ConstantDataArray::getString(context, str, true);
    }
    return nullptr;
}
