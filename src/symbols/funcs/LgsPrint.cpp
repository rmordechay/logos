#include "funcs/LgsPrint.h"
#include "CodeGenMetadata.h"

Value* LgsPrint::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    if (!IRFunc) setIRFunc(metadata);
    auto argValue = args[0]->getIRValue(metadata);
    return metadata->builder.CreateCall(IRFunc, {argValue});
}

void LgsPrint::setIRFunc(CodeGenMetadata* metadata) {
    vector<Type*> paramTypes;
    for (const auto& param : params) {
        paramTypes.emplace_back(param->type->getIRType());
    }
    const auto IRFuncType = FunctionType::get(Type::getVoidTy(context), paramTypes, false);
    IRFunc = Function::Create(IRFuncType, GlobalValue::ExternalLinkage, signature.composedName, metadata->currentModule);
}

void LgsPrint::createIRValue(CodeGenMetadata* metadata) {}
