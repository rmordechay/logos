#include "funcs/LgsPrint.h"
#include "CodeGenMetadata.h"

Function* LgsPrint::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) setIRFuncType();
    auto func = metadata->currentModule->getOrInsertFunction(signature.composedName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

void LgsPrint::createIRValue(CodeGenMetadata* metadata) {
    setIRFuncType();
}

Value* LgsPrint::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto IRFunc = getIRFunc(metadata);
    auto argValue = args[0]->getIRValue(metadata);
    return metadata->builder.CreateCall(IRFunc, {argValue});
}

void LgsPrint::setIRFuncType() {
    vector<Type*> paramTypes;
    for (const auto& param : signature.params) {
        paramTypes.emplace_back(param->type->getIRType());
    }
    IRFuncType = FunctionType::get(Type::getVoidTy(context), paramTypes, false);
}
