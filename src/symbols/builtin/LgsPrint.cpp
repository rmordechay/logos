#include "builtin/LgsPrint.h"
#include "CodeGenMetadata.h"

void LgsPrint::setIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> paramTypes;
    for (const auto& param : funcType.params) {
        paramTypes.emplace_back(param.type->getIRType());
    }
    IRFuncType = FunctionType::get(funcType.type->getIRType(), paramTypes, false);
}

