#include "funcs/LogosMethodImpl.h"

#include "exprs/LogosConstant.h"

#include <LogosDefinitions.h>
#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    const auto objSymbol = metadata->logosStack.getSymbol(parentName);
    const auto objType = objSymbol->object->getIRType();
    const auto method = Function::Create(getMethodType(objType), Function::ExternalLinkage, combinedName, metadata->currentModule);
    metadata->logosStack.enterScope(method);

    auto args = method->arg_begin();
    args++->setName(LOGOS_THIS);
    metadata->logosStack.addLocalSymbol(LOGOS_THIS, *objSymbol);
    setIRArgs(metadata, params, args);

    startBlock(metadata, funcEntry);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return method;
}

Value* LogosMethodImpl::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    vector<Type*> paramTypes;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        paramValues.emplace_back(argValue);
        paramTypes.emplace_back(argValue->getType());
    }
    const auto methodType = FunctionType::get(type->getIRType(), paramTypes, false);
    const auto method = metadata->currentModule->getOrInsertFunction(combinedName, methodType);
    return metadata->builder.CreateCall(method, paramValues);
}

FunctionType* LogosMethodImpl::getMethodType(Type* structType) const {
    vector<Type*> IRParams;
    IRParams.emplace_back(structType);
    for (const auto& param : params) {
        IRParams.emplace_back(param->inferredType->getIRType());
    }
    return FunctionType::get(type->getIRType(), IRParams, false);
}

Value* LogosMethodImpl::callFunc(CodeGenMetadata* metadata) {
    return callFunc(metadata, vector<LogosExpr*>());
}