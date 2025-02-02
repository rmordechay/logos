#include "LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto printFuncType = FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(), false);
    return Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
}

FunctionCallee LogosPrint::getFuncCallee(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const vector<Type*> paramTypes = {builder->getPtrTy(), builder->getInt32Ty()};
    const auto funcType = FunctionType::get(builder->getVoidTy(), paramTypes, false);
    return module->getOrInsertFunction("printInt", funcType);
}

vector<Value*> LogosPrint::getArgs(IRBuilder<>* builder, LogosStack* theStack, Module* module, const vector<LogosExpr*>& args) {
    const auto arg = args[0];
    const auto llvmValue = arg->getLLVMValue(builder, theStack, module);

    vector<Value*> llvmArgs;
    string str;
    Constant* llvmStr;
    if (const auto constInt = dyn_cast<ConstantInt>(llvmValue)) {
        str = std::to_string(constInt->getSExtValue());
        llvmStr = builder->CreateGlobalStringPtr(str);
    }
    llvmArgs.emplace_back(llvmStr);
    llvmArgs.emplace_back(builder->getInt32(str.size()));
    return llvmArgs;
}
