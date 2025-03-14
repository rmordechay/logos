#include "funcs/LgsMethodImpl.h"

#include "LgsInstance.h"
#include "constants/LgsConstant.h"
#include <types/LgsObject.h>

Value* LgsMethodImpl::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    setIRFunc(metadata);

    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->getIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

Value* LgsMethodImpl::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    if (!IRFunc) setIRFunc(metadata);
    const auto functionType = IRFunc->getFunctionType();
    const auto IRFunc = metadata->currentModule->getOrInsertFunction(combinedName, functionType);
    return metadata->builder.CreateCall(IRFunc, argValues);
}

void LgsMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    const auto selfPtr = params[0]->type->getIRType()->getPointerTo();
    IRParamsTypes.emplace_back(selfPtr);
    for (int i = 1; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    IRFunc = Function::Create(rt, Function::ExternalLinkage, combinedName, metadata->currentModule);
    metadata->logosStack.currentFunc = IRFunc;
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, LgsSymbol(PARAM, param));
    }
}

void LgsMethodImpl::setCombinedName() {
    combinedName = parentName + "_" + name;
    combinedName += "_" + type->getName();
    for (int i = 1; i < params.size(); ++i) {
        combinedName += "_" + params[i]->type->getName();
    }
}
