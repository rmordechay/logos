#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::getLLVMValue(CodeGenMetadata* metadata) {
    const auto printFuncType = FunctionType::get(metadata->builder->getVoidTy(), metadata->builder->getInt32Ty(), false);
    llvmValue = Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
    return llvmValue;
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto llvmArgs = getArgs(metadata, args);
    const auto func = getFuncCallee(metadata);
    llvmValue = metadata->builder->CreateCall(func, llvmArgs);
    return llvmValue;
}

FunctionCallee LogosPrint::getFuncCallee(CodeGenMetadata* metadata) {
    const vector<Type*> paramTypes = {metadata->builder->getPtrTy(), metadata->builder->getInt32Ty()};
    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), paramTypes, false);
    auto func = metadata->module->getOrInsertFunction("printInt", funcType);
    return func;
}

vector<Value*> LogosPrint::getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto arg = args[0];
    const auto llvmValue = arg->getLLVMValue(metadata);

    vector<Value*> llvmArgs;
    string str;
    Constant* llvmStr;
    if (const auto constInt = dyn_cast<ConstantInt>(llvmValue)) {
        str = std::to_string(constInt->getSExtValue());
        llvmStr = metadata->builder->CreateGlobalStringPtr(str);
    }
    llvmArgs.emplace_back(llvmStr);
    llvmArgs.emplace_back(metadata->builder->getInt32(str.size()));
    return llvmArgs;
}
