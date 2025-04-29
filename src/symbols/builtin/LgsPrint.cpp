#include "builtin/LgsPrint.h"
#include "CodeGenMetadata.h"

void LgsPrint::setIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> paramTypes;
    for (const auto& param : signature.params) {
        paramTypes.emplace_back(param.type->getIRType());
    }
    IRFuncType = FunctionType::get(signature.type->getIRType(), paramTypes, false);
}

