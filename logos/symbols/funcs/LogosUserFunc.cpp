#include "LogosUserFunc.h"

const LogosType& LogosUserFunc::getType() const {
    return type;
}

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.push_back(param->getLLVMType(builder));
    }
    const auto funcType = FunctionType::get(type.getLLVMType(builder), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    auto args = func->arg_begin();
    args->setName();
    for (const auto param : params) {
        args++;
    }
    const auto addEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(addEntry);
    Value* a = fooFunc->getArg(0); // First parameter
    Value* b = fooFunc->getArg(1); // Second parameter

    // Example: Add the two parameters
    Value* sum = builder.CreateAdd(a, b, "sum");
    return builder->CreateRetVoid();
}
