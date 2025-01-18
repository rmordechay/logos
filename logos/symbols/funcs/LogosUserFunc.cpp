#include "LogosUserFunc.h"

#include "LogosSymbol.h"

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.push_back(param->type->getLLVMType(builder));
    }
    const auto funcType = FunctionType::get(type->getLLVMType(builder), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    auto arg = func->arg_begin();
    for (const auto param : params) {
        auto argName = param->name;
        stackFrame->symbolTable[argName] = arg;
        arg++;
    }
    const auto funcEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(funcEntry);

    for (const auto stmt : stmts) {
        stmt->getLLVMValue(builder, stackFrame, module);
    }

    stackFrame->currentFunction = func;
    stackFrame->functions[name] = func;
    return func;
}
