#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

Value* LogosFuncCall::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto callee = metadata->theStack->getSymbol(name)->func;
    const auto llvmArgs = callee->getArgs(metadata, args);
    const auto func = callee->getFuncCallee(metadata);
    llvmValue = metadata->builder->CreateCall(func, llvmArgs);
    return llvmValue;
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto arg : args) {
        delete arg;
    }
}
