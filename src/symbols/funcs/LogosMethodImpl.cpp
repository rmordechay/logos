#include "funcs/LogosMethodImpl.h"

#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    const auto objSymbol = metadata->logosStack.getSymbol(parentName);
    const auto objType = objSymbol->object->getIRType();

    vector<Type*> IRParams;
    IRParams.emplace_back(objType);
    for (const auto& param : params) {
        IRParams.emplace_back(param->inferredType->getIRType());
    }
    const auto methodType = FunctionType::get(type->getIRType(), IRParams, false);

    const auto method = Function::Create(methodType, Function::ExternalLinkage, combinedName, metadata->currentModule);
    const auto methodEntry = BasicBlock::Create(context, "entry", method);
    metadata->builder.SetInsertPoint(methodEntry);
    metadata->logosStack.currentFunc = method;

    metadata->logosStack.addLocalSymbol("this", *objSymbol);
    auto args = method->arg_begin();
    for (const auto& param : params) {
        metadata->logosStack.addLocalSymbol(param->name, LogosSymbol::createSymbolFromExpr(param->expr));
        args++;
    }

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