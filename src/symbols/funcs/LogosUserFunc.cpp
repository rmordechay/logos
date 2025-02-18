#include "funcs/LogosUserFunc.h"

#include "LogosUtils.h"

#include <LogosStack.h>

Value* LogosUserFunc::computeIRValue(CodeGenMetadata* metadata) {
    const auto func = Function::Create(getIRFunc(), Function::ExternalLinkage, getFuncName(), metadata->module);
    metadata->theStack->enterScope(func);
    auto arg = func->arg_begin();
    for (const auto& param : params) {
        metadata->theStack->addLocalSymbol(param->name, Utils::createSymbol(param->expr));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(context, "entry", func);
    metadata->builder->SetInsertPoint(funcEntry);
    stmtBlock->getIRValue(metadata);
    metadata->theStack->exitScope();
    return func;
}

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    vector<Type*> paramTypes;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        paramValues.emplace_back(argValue);
        paramTypes.emplace_back(argValue->getType());
    }
    const auto funcType = FunctionType::get(type->getIRType(), paramTypes, false);
    const auto func = metadata->module->getOrInsertFunction(getFuncName(), funcType);
    return metadata->builder->CreateCall(func, paramValues);
}

FunctionType* LogosUserFunc::getIRFunc() const {
    vector<Type*> IRParams;
    for (const auto& param : params) {
        IRParams.emplace_back(param->inferredType->getIRType());
    }
    return FunctionType::get(type->getIRType(), IRParams, false);
}

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata) {
    return callFunc(metadata, vector<LogosExpr*>());
}

string LogosUserFunc::getFuncName() const {
    string funcName;
    if (parentName == "") {
        funcName = name;
    } else {
        funcName = parentName + "_" + name;
    }
    return funcName;
}
