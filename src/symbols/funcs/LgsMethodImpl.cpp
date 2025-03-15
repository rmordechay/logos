#include "funcs/LgsMethodImpl.h"

#include "LgsInstance.h"
#include <types/LgsObject.h>

Value* LgsMethodImpl::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    setIRFunc(metadata);

    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->getIRValue(metadata);
    metadata->logosStack.exitScope();
    return IRFunc;
}

Value* LgsMethodImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    if (!IRFunc) setIRFunc(metadata);
    const auto functionType = IRFunc->getFunctionType();
    const auto IRFunc = metadata->currentModule->getOrInsertFunction(IRName, functionType);
    return metadata->builder.CreateCall(IRFunc, argValues);
}

void LgsMethodImpl::setIRNames() {
    IRName = parentName + "_" + name;
    IRName += "_" + type->getName();
    for (int i = 1; i < params.size(); ++i) {
        IRName += "_" + params[i]->type->getName();
    }
}

void LgsMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    const auto selfPtr = params[0]->type->getIRType()->getPointerTo();
    IRParamsTypes.emplace_back(selfPtr);
    for (int i = 1; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    IRFunc = Function::Create(rt, Function::ExternalLinkage, IRName, metadata->currentModule);
    metadata->logosStack.currentFunc = IRFunc;
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
}