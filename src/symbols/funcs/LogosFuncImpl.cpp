#include "funcs/LogosFuncImpl.h"
#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosFuncImpl::computeIRValue(CodeGenMetadata* metadata) {
    setCombinedName();
    metadata->logosStack.enterScope();
    setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;

    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->writeIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

void LogosFuncImpl::setIRFunc(CodeGenMetadata* metadata) {
    for (int i = 0; i < params.size(); ++i) {
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

void LogosFuncImpl::setCombinedName() {
    if (name == LOGOS_MAIN_FUNC) {
        combinedName = name;
    } else {
        combinedName = name + "_" + type->getName();
        for (int i = 1; i < params.size(); ++i) {
            combinedName += "_" + params[i]->type->getName();
        }
    }
}
