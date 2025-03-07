#include "funcs/LogosMethodImpl.h"
#include "exprs/LogosConstant.h"
#include <LogosDefinitions.h>
#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    IRFunc = getIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;

    startBlock(metadata, entryBlock);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return IRFunc;
}

Value* LogosMethodImpl::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> argsValues;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        argsValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, argsValues);
}

Value* LogosMethodImpl::callFunc(CodeGenMetadata* metadata) {
    return callFunc(metadata, vector<LogosExpr*>());
}

Function* LogosMethodImpl::getIRFunc(CodeGenMetadata* metadata) {
    const auto obj = metadata->logosStack.getSymbol(parentName)->object;
    IRParamsTypes.emplace_back(obj->getIRType()->getPointerTo());
    for (const auto& param : params) {
        IRParamsTypes.emplace_back(param->type->getIRType());
    }

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    const auto method = Function::Create(rt, Function::ExternalLinkage, combinedName, metadata->currentModule);

    auto args = method->arg_begin();
    args++->setName(LOGOS_THIS);
    metadata->logosStack.addLocalSymbol(LOGOS_THIS, LogosSymbol(OBJECT, obj));
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, LogosSymbol(PARAM, param));
    }

    return method;
}
