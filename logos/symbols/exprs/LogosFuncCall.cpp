#include "LogosFuncCall.h"

#include <iostream>
#include <ostream>

Value* LogosFuncCall::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto funcSymbol = stackFrame->getFunc(name);
    std::vector<Value*> llvmArgs;
    for (const auto arg : args) {
        llvmArgs.push_back(arg->getLLVMValue(builder, stackFrame, module));
    }
    return builder->CreateCall(funcSymbol, ArrayRef(llvmArgs));
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto arg : args) {
        delete arg;
    }
}
