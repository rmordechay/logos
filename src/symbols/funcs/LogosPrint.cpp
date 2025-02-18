#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::computeIRValue(CodeGenMetadata* metadata) {
    const auto printFuncType = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    return Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    vector<Value*> IRArgs;
    const auto argValue = args[0]->writeIRValue(metadata);
    IRArgs.emplace_back(argValue);

    const auto builder = metadata->builder;
    const auto funcType = FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(), false);
    const auto func = metadata->module->getOrInsertFunction(IRName, funcType);

    return builder->CreateCall(func, IRArgs);
}
