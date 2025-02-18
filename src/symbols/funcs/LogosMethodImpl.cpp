#include "funcs/LogosMethodImpl.h"

#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    const auto symbol = metadata->logosStack.getSymbol(parentName);
    const auto structType = symbol->object->getIRType();
    const auto funcType = getIRFuncType(structType);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, combinedName, metadata->currentModule);
    const auto funcEntry = BasicBlock::Create(context, "entry", func);
    metadata->builder.SetInsertPoint(funcEntry);
    metadata->logosStack.currentFunc = func;

    metadata->logosStack.addLocalSymbol("this", *symbol);
    auto arg = func->arg_begin();
    for (const auto& param : params) {
        metadata->logosStack.addLocalSymbol(param->name, LogosSymbol::createSymbolFromExpr(param->expr));
        arg++;
    }

    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return func;
}

Value* LogosMethodImpl::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    vector<Type*> paramTypes;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        paramValues.emplace_back(argValue);
        paramTypes.emplace_back(argValue->getType());
    }
    const auto funcType = FunctionType::get(type->getIRType(), paramTypes, false);
    const auto func = metadata->currentModule->getOrInsertFunction(combinedName, funcType);
    return metadata->builder.CreateCall(func, paramValues);
}

FunctionType* LogosMethodImpl::getIRFuncType(Type* structType) const {
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