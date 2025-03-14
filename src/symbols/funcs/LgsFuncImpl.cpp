#include "funcs/LgsFuncImpl.h"
#include <LgsStack.h>
#include <types/LgsInt.h>

Value* LgsFuncImpl::createIRValue(CodeGenMetadata* metadata) {
    setCombinedName();
    metadata->logosStack.enterScope();
    setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;

    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->getIRValue(metadata);
    metadata->logosStack.exitScope();
    return nullptr;
}

Value* LgsFuncImpl::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    vector<Value*> paramValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        paramValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(symbol->funcImpl->IRFunc, paramValues);
}

void LgsFuncImpl::setIRFunc(CodeGenMetadata* metadata) {
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
        metadata->logosStack.addLocalSymbol(param->name, param);
    }
}

void LgsFuncImpl::setCombinedName() {
    if (name == LOGOS_MAIN_FUNC) {
        combinedName = name;
    } else {
        combinedName = name + "_" + type->getName();
        for (int i = 1; i < params.size(); ++i) {
            combinedName += "_" + params[i]->type->getName();
        }
    }
}
