#include "LogosUserFunc.h"

FunctionCallee LogosUserFunc::getFuncCallee(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    return nullptr;
}

vector<Value*> LogosUserFunc::getArgs(IRBuilder<>* builder, LogosStack* theStack, Module* module, const vector<LogosExpr*>& args) {
    return vector<Value*>();
}

Value* LogosUserFunc::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    std::vector<Type*> llvmParams;
    for (const auto param : params) {
        llvmParams.emplace_back(param->inferredType->getLLVMType(builder, theStack));
    }

    const auto funcType = FunctionType::get(type->getLLVMType(builder, theStack), llvmParams, false);
    const auto func = Function::Create(funcType, Function::ExternalLinkage, name, module);
    theStack->enterScope(func);

    auto arg = func->arg_begin();
    for (const auto param : params) {
        theStack->addSymbol(param->name, LogosSymbol(VAR_DEC, param));
        arg++;
    }

    const auto funcEntry = BasicBlock::Create(builder->getContext(), "entry", func);
    builder->SetInsertPoint(funcEntry);

    for (const auto stmt : stmts) {
        stmt->getLLVMValue(builder, theStack, module);
    }

    theStack->exitScope();
    return func;
}

