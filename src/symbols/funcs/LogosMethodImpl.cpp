#include "funcs/LogosMethodImpl.h"
#include "unary/constants/LogosConstant.h"
#include <LogosDefinitions.h>
#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    combinedName = obj->getName() + "_" + name+ "_" + type->getName();
    metadata->logosStack.enterScope();
    IRFunc = getIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;

    startBlock(metadata, entryBlock);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

Value* LogosMethodImpl::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> argsValues;
    for (const auto& arg : args) {
        const auto argValue = arg->writeIRValue(metadata);
        argsValues.emplace_back(argValue);
    }
    const auto func = metadata->currentModule->getOrInsertFunction(combinedName, IRFunc->getFunctionType());
    return metadata->builder.CreateCall(func, argsValues);
}

Function* LogosMethodImpl::getIRFunc(CodeGenMetadata* metadata) {
    for (const auto& param : params) {
        IRParamsTypes.emplace_back(param->type->getIRType());
    }
    IRParamsTypes.emplace_back(obj->getIRType()->getPointerTo());
    metadata->logosStack.addLocalSymbol(LOGOS_THIS, LogosSymbol(OBJECT, obj));

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    const auto method = Function::Create(rt, Function::ExternalLinkage, combinedName, metadata->currentModule);
    if (params.size() == 1) return method;

    auto args = method->arg_begin();
    setArgs(metadata, args);
    args->setName(LOGOS_THIS);
    return method;
}
