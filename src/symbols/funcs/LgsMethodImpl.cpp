#include "funcs/LgsMethodImpl.h"

#include "exprs/unary/LgsInstance.h"
#include <types/LgsObject.h>

Value* LgsMethodImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    if (!IRFunc) setIRFunc(metadata);
    const auto functionType = IRFunc->getFunctionType();
    const auto IRFunc = metadata->currentModule->getOrInsertFunction(composedName, functionType);
    return metadata->builder.CreateCall(IRFunc, argValues);
}

void LgsMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    const auto selfPtr = params[0]->type->getIRType()->getPointerTo();
    IRParamsTypes.emplace_back(selfPtr);
    for (int i = 1; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    IRFunc = Function::Create(rt, Function::ExternalLinkage, composedName, metadata->currentModule);
    metadata->logosStack.currentFunc = IRFunc;
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
}