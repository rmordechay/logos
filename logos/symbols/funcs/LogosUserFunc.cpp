#include "LogosUserFunc.h"

#include "LogosSymbol.h"

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.push_back(param->type->getLLVMType(builder));
    }
    const auto funcType = FunctionType::get(type->getLLVMType(builder), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    auto arg = func->arg_begin();
    for (const auto param : params) {
        auto argName = param->name;
        stackFrame->top().symbolTable[argName] = arg;
        arg++;
    }
    stackFrame->top().currentFunction = func;
    stackFrame->top().functions[name] = func;

    const auto funcEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(funcEntry);

    for (const auto stmt : stmts) {
        stmt->getLLVMValue(builder, stackFrame, module);
    }
    return func;
}
