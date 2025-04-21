#include "builtin/LgsPrint.h"
#include "CodeGenMetadata.h"

void LgsPrint::createIRFunc(CodeGenMetadata* metadata) {}

Function* LgsPrint::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) {
        vector<Type*> paramTypes;
        for (const auto& param : signature.params) {
            paramTypes.emplace_back(param.type->getIRType());
        }
        IRFuncType = FunctionType::get(Type::getVoidTy(context), paramTypes, false);
    }
    assert(IRFuncType);
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

