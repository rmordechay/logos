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
    auto args = func->arg_begin();
    for (const auto param : params) {
        args++;
    }
    Value* a = func->getArg(0);
    Value* b = func->getArg(1);
    const auto addEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(addEntry);
    Value* sum = builder->CreateAdd(a, b, "sum");
    return builder->CreateRetVoid();
}
