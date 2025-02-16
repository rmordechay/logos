#include "funcs/LogosUserFunc.h"

Value* LogosUserFunc::getLLVMValue(CodeGenMetadata* metadata) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.emplace_back(param->inferredType->getLLVMType());
    }

    const auto funcType = FunctionType::get(type->getLLVMType(), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, metadata->module);
    metadata->theStack->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto param : params) {
        metadata->theStack->addLocalSymbol(param->name, param->expr->createSymbol());
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(context, "entry", func);
    metadata->builder->SetInsertPoint(funcEntry);
    stmtBlock->getLLVMValue(metadata);
    llvmValue = func;

    metadata->theStack->exitScope();
    return func;
}

vector<Value*> LogosUserFunc::getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    return vector<Value*>();
}

FunctionCallee LogosUserFunc::getFuncCallee(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    if (llvmValue) return llvmValue;
    const auto llvmArgs = getArgs(metadata, args);
    const auto func = getFuncCallee(metadata);
    llvmValue = metadata->builder->CreateCall(func, llvmArgs);
    return llvmValue;
}
