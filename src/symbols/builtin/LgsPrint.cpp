#include "builtin/LgsPrint.h"
#include "CodeGenMetadata.h"

vector<Type*> LgsPrint::getIRParamTypes(const CodeGenMetadata* metadata) {
    vector<Type*> paramTypes;
    for (const auto& param : signature.params) {
        paramTypes.emplace_back(param.type->getIRType());
    }
    return paramTypes;
}

