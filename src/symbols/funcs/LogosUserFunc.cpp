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
        llvmParams.emplace_back(param->inferredType->getLLVMType(metadata->builder, metadata->theStack));
    }

    const auto funcType = FunctionType::get(type->getLLVMType(metadata->builder, metadata->theStack), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, metadata->module);
    metadata->theStack->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto param : params) {
        metadata->theStack->addSymbol(param->name, LogosSymbol(VAR_DEC, param));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(metadata->builder->getContext(), "entry", func);
    metadata->builder->SetInsertPoint(funcEntry);

    for (const auto stmt : stmts) {
        stmt->getLLVMValue(metadata);
    }

    metadata->theStack->exitScope();
    return func;
}

