#include "LogosFuncCall.h"

#include <iostream>
#include <ostream>


void LogosFuncCall::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

Value* LogosFuncCall::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto funcSymbol = stackFrame->globalFuncs[name];
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