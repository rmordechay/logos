#include "funcs/LogosFuncImpl.h"
#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosFuncImpl::computeIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    IRFunc = getIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;

    startBlock(metadata, entryBlock);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

Value* LogosFuncImpl::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        paramValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, paramValues);
}

Value* LogosFuncImpl::call(CodeGenMetadata* metadata) {
    return call(metadata, vector<LogosExpr*>());
}

Function* LogosFuncImpl::getIRFunc(CodeGenMetadata* metadata) {
    for (const auto& param : params) {
        IRParamsTypes.emplace_back(param->type->getIRType());
    }

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    const auto func = Function::Create(rt, Function::ExternalLinkage, name, metadata->currentModule);
    if (params.empty()) return func;

    auto args = func->arg_begin();
    setArgs(metadata, args);
    return func;
}
