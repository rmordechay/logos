#include "LogosFuncCallExpr.h"

#include <iostream>
#include <ostream>

Value* LogosFuncCallExpr::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    const auto funcSymbol = stackFrame->top().functions[name];
    std::vector<Value*> llvmArgs;
    for (const auto arg : args) {
        llvmArgs.push_back(arg->getLLVMValue(builder, stackFrame, module));
    }
    return builder->CreateCall(funcSymbol, ArrayRef(llvmArgs));
}

LogosFuncCallExpr::~LogosFuncCallExpr() {
    for (const auto arg : args) {
        delete arg;
    }
}
