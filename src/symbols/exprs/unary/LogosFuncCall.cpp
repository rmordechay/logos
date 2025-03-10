#include "unary/LogosFuncCall.h"

#include <LogosStack.h>
#include "funcs/LogosFunc.h"
#include "funcs/LogosFuncImpl.h"

#include <funcs/LogosBuiltinFunc.h>

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    if (symbol->type == BUILTIN_FUNC) {
        return symbol->builtinFunc->call(metadata, args);
    }
    if (symbol->type == FUNC_IMPL) {
        vector<Value*> paramValues;
        for (const auto& arg : args) {
            const auto argValue = arg->writeIRValue(metadata);
            paramValues.emplace_back(argValue);
        }
        return metadata->builder.CreateCall(symbol->funcImpl->IRFunc, paramValues);
    }
    return nullptr;
}

string LogosFuncCall::getName() {
    return name;
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
