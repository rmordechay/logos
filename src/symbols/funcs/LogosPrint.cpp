#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::getLLVMValue(CodeGenMetadata* metadata) {
    const auto printFuncType = FunctionType::get(LOGOS_VOID.llvmType, LOGOS_INT.llvmType, false);
    llvmValue = Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
    return llvmValue;
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    if (llvmValue) return llvmValue;
    string str;
    Constant* llvmStr;
    vector<Value*> llvmArgs;

    const auto argValue = args[0]->getLLVMValue(metadata);
    if (const auto constInt = dyn_cast<ConstantInt>(argValue)) {
        str = to_string(constInt->getSExtValue());
        llvmStr = metadata->builder->CreateGlobalStringPtr(str);
    }
    llvmArgs.emplace_back(llvmStr);
    llvmArgs.emplace_back(metadata->builder->getInt32(str.size()));

    const vector<Type*> paramTypes = {metadata->builder->getPtrTy(), metadata->builder->getInt32Ty()};
    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), paramTypes, false);
    auto func = metadata->module->getOrInsertFunction(llvmName, funcType);
    func.getCallee()->print(outs());
    llvmValue = metadata->builder->CreateCall(func, llvmArgs);
    return llvmValue;
}
