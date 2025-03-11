#include "unary/LogosMethodCall.h"

#include "LogosInstance.h"
#include "funcs/LogosMethodImpl.h"

Value* LogosMethodCall::createIRValue(CodeGenMetadata* metadata) {
    vector<Value*> paramValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        paramValues.emplace_back(argValue);
    }
    const auto funcType = methodImpl->IRFunc->getFunctionType();
    const auto func = metadata->currentModule->getOrInsertFunction(methodImpl->combinedName, funcType);
    return metadata->builder.CreateCall(func, paramValues);
}

string LogosMethodCall::getName() {
    return name;
}

LogosMethodCall::~LogosMethodCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
