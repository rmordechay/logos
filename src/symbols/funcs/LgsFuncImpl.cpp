#include "funcs/LgsFuncImpl.h"
#include <LgsStack.h>
#include <types/LgsInt.h>

Value* LgsFuncImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    if (!IRFunc) setIRFunc(metadata);
    const auto symbol = metadata->logosStack.getSymbol(signature.composedName);
    vector<Value*> paramValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        paramValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(symbol->func->IRFunc, paramValues);
}

void LgsFuncImpl::setIRFunc(CodeGenMetadata* metadata) {
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    IRFunc = Function::Create(rt, Function::ExternalLinkage, signature.composedName, metadata->currentModule);
    metadata->logosStack.currentFunc = IRFunc;
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
}
