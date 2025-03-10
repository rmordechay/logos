#include "funcs/LogosMethodImpl.h"
#include "constants/LogosConstant.h"
#include <object/LogosObject.h>

Value* LogosMethodImpl::computeIRValue(CodeGenMetadata* metadata) {
    setCombinedName();
    metadata->logosStack.enterScope();
    setIRFunc(metadata);

    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

void LogosMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    auto selfIRType = params[0]->type->getIRType()->getPointerTo();
    IRParamsTypes.emplace_back(selfIRType);
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
        metadata->logosStack.addLocalSymbol(param->name, LogosSymbol(PARAM, param));
    }
}

void LogosMethodImpl::setCombinedName() {
    combinedName = parentObj->getName() + "_" + name;
    combinedName += "_" + type->getName();
    for (int i = 1; i < params.size(); ++i) {
        combinedName += "_" + params[i]->type->getName();
    }
}
