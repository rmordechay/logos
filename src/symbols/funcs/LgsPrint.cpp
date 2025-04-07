#include "funcs/LgsPrint.h"
#include "CodeGenMetadata.h"

void LgsPrint::createIRValue(CodeGenMetadata* metadata) {
    setIRFuncType();
}

void LgsPrint::setIRFuncType() {
    vector<Type*> paramTypes;
    for (const auto& param : signature.params) {
        paramTypes.emplace_back(param.type->getIRType());
    }
    IRFuncType = FunctionType::get(Type::getVoidTy(context), paramTypes, false);
}
