#include "LogosUserFunc.h"

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.push_back(param->type->getLLVMType(builder));
    }

    const auto funcType = FunctionType::get(type->getLLVMType(builder), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    stackFrame->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto param : params) {
        stackFrame->addSymbol(param->name, new LogosSymbol(arg));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(funcEntry);

    for (const auto stmt : stmts) {
        stmt->getLLVMValue(builder, stackFrame, module);
    }

    stackFrame->exitScope();
    return func;
}
