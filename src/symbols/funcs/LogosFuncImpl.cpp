#include "funcs/LogosFuncImpl.h"
#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosFuncImpl::computeIRValue(CodeGenMetadata* metadata) {
    const auto func = Function::Create(getIRFunc(), Function::ExternalLinkage, name, metadata->currentModule);
    metadata->logosStack.enterScope(func);

    const auto args = func->arg_begin();
    setIRParams(metadata, args);

    startBlock(metadata, funcEntry);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return func;
}

FunctionType* LogosFuncImpl::getIRFunc() const {
    vector<Type*> IRParams;
    for (const auto& param : params) {
        IRParams.emplace_back(param->type->getIRType());
    }
    return FunctionType::get(type->getIRType(), IRParams, false);
}

Value* LogosFuncImpl::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    vector<Type*> paramTypes;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        paramValues.emplace_back(argValue);
        paramTypes.emplace_back(argValue->getType());
    }
    const auto funcType = FunctionType::get(type->getIRType(), paramTypes, false);
    const auto func = metadata->currentModule->getOrInsertFunction(name, funcType);
    return metadata->builder.CreateCall(func, paramValues);
}

Value* LogosFuncImpl::callFunc(CodeGenMetadata* metadata) {
    return callFunc(metadata, vector<LogosExpr*>());
}