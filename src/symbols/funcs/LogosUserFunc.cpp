#include "funcs/LogosUserFunc.h"

Value* LogosUserFunc::getLLVMValue(CodeGenMetadata* metadata) {
    std::vector<Type*> llvmParams;
    for (const auto& param : params) {
        llvmParams.emplace_back(param->inferredType->getLLVMType());
    }

    const auto funcType = FunctionType::get(type->getLLVMType(), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, metadata->module);
    metadata->theStack->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto& param : params) {
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

Value* LogosUserFunc::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    if (llvmValue) return llvmValue;
    vector<Value*> llvmArgs;

    for (const auto& arg : args) {
        const auto argValue = arg->getLLVMValue(metadata);
        if (const auto constInt = dyn_cast<ConstantInt>(argValue)) {
            auto name = std::to_string(constInt->getSExtValue());
            auto llvmStr = metadata->builder->CreateGlobalStringPtr(name);
            llvmArgs.emplace_back(llvmStr);
            llvmArgs.emplace_back(metadata->builder->getInt32(name.size()));
        } else {
            llvmArgs.emplace_back(argValue);
        }
    }

    const vector<Type*> paramTypes = {metadata->builder->getPtrTy(), metadata->builder->getInt32Ty()};
    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), paramTypes, false);
    const auto func = metadata->module->getOrInsertFunction("printInt", funcType);
    llvmValue = metadata->builder->CreateCall(func, llvmArgs);
    return llvmValue;
}
