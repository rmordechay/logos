#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

void LogosFuncCall::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

Value* LogosFuncCall::getLLVMValue(CodeGenMetadata* metadata) {
    const auto callee = metadata->theStack->getSymbol(name)->func;
    const auto llvmArgs = callee->getArgs(metadata, args);
    const auto func = callee->getFuncCallee(metadata);
    return metadata->builder->CreateCall(func, llvmArgs);
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto arg : args) {
        delete arg;
    }
}
