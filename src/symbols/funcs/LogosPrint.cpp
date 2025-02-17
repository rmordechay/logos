#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto printFuncType = FunctionType::get(LOGOS_VOID.llvmType, LOGOS_INT.llvmType, false);
    return Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> llvmArgs;
    const auto argValue = args[0]->getLLVMValue(metadata);
    llvmArgs.emplace_back(argValue);
    // if (const auto function = dyn_cast<Function>(argValue)) {
    //     auto funcType = function->getFunctionType()->getContainedType(0);
    // } else {
    //
    // }

    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), metadata->builder->getInt32Ty(), false);
    const auto func = metadata->module->getOrInsertFunction(llvmName, funcType);

    return metadata->builder->CreateCall(func, llvmArgs);
}
