#include "funcs/LogosUserFunc.h"

FunctionCallee LogosUserFunc::getFuncCallee(CodeGenMetadata* metadata) {
    return nullptr;
}

vector<Value*> LogosUserFunc::getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    return vector<Value*>();
}

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
        // TODO add param object to differentiate from var dec
        metadata->theStack->addLocalSymbol(param->name, LogosSymbol(VAR_DEC, param));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(context, "entry", func);
    metadata->builder->SetInsertPoint(funcEntry);
    stmtBlock->getLLVMValue(metadata);
    llvmValue = func;

    metadata->theStack->exitScope();
    return func;
}

