#include "funcs/LgsFuncImpl.h"
#include <LgsStack.h>
#include <types/LgsInt.h>

Value* LgsFuncImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto symbol = metadata->logosStack.getSymbol(composedName);
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

    auto result = type->getIRType();
    const auto rt = FunctionType::get(result, IRParamsTypes, false);
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

json LgsFuncImpl::asJson() {
    json tree;
    tree["name"] = name;
    tree["returnType"] = type->getName();
    tree["params"] = {};
    for (const auto& param : params) {
        tree["params"].emplace_back(param->asJson());
    }
    return tree;
}
