#include "funcs/LogosUserFunc.h"

#include "LogosUtils.h"

Value* LogosUserFunc::computeLLVMValue(CodeGenMetadata* metadata) {
    vector<Type*> llvmParams;
    for (const auto& param : params) {
        llvmParams.emplace_back(param->inferredType->getLLVMType());
    }

    const auto funcType = FunctionType::get(type->getLLVMType(), llvmParams, false);
    string funcName = name;
    if (parentName != "") {
        funcName = parentName + "_" + funcName;
    }
    const auto func = Function::Create(funcType, Function::ExternalLinkage, funcName, metadata->module);
    metadata->theStack->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto& param : params) {
        metadata->theStack->addLocalSymbol(param->name, Utils::createSymbol(param->expr));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(context, "entry", func);
    metadata->builder->SetInsertPoint(funcEntry);
    stmtBlock->getLLVMValue(metadata);

    metadata->theStack->exitScope();
    return func;
}

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> paramValues;
    vector<Type*> paramTypes;
    for (const auto& arg : args) {
        const auto argValue = arg->getLLVMValue(metadata);
        paramValues.emplace_back(argValue);
        paramTypes.emplace_back(argValue->getType());
    }

    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), paramTypes, false);
    string funcName;
    if (parentName == "") {
        funcName = name;
    } else {
        funcName = parentName + "_" + funcName;
    }
    const auto func = metadata->module->getOrInsertFunction(funcName, funcType);
    return metadata->builder->CreateCall(func, paramValues);
}

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata) {
    return callFunc(metadata, vector<LogosExpr*>());
}
