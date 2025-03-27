#include "funcs/LgsMethodImpl.h"

#include "exprs/unary/LgsInstance.h"
#include <types/LgsObject.h>

Value* LgsMethodImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    if (!IRFunc) setIRFunc(metadata);
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, argValues);
}

void LgsMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    IRParamsTypes.emplace_back(ptrTy);
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto functionType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    auto func = metadata->currentModule->getOrInsertFunction(signature.composedName, functionType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    metadata->logosStack.currentFunc = IRFunc;
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
}