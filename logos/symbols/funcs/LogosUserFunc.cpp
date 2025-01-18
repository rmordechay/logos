#include "LogosUserFunc.h"

const LogosType& LogosUserFunc::getType() const {
    return type;
}

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.push_back(param->type.getLLVMType(builder));
    }
    const auto funcType = FunctionType::get(type.getLLVMType(builder), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    if (params.size() > 0) {
        auto args = func->arg_begin();
        args->setName(params[0]->name);
        for (int i = 1; i < params.size(); ++i) {
            args++->setName(params[i]->name);
        }
    }
    const auto addEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(addEntry);
    builder->CreateAlloca(builder->getInt1Ty());
    stackFrame->currentFunction = func;
    return builder->CreateRetVoid();
}
