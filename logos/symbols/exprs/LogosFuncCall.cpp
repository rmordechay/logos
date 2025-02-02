#include "LogosFuncCall.h"

#include <iostream>
#include <ostream>
#include <llvm/IR/Module.h>


void LogosFuncCall::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

Value* LogosFuncCall::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto callee = theStack->globalSymbols[name].func;
    const auto llvmArgs = callee->getArgs(builder, theStack, module, args);
    const auto func = callee->getFuncCallee(builder, theStack, module);
    return builder->CreateCall(func, llvmArgs);
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto arg : args) {
        delete arg;
    }
}