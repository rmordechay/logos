#include "unary/LogosMethodCall.h"

#include "LogosInstance.h"
#include "funcs/LogosMethodImpl.h"

Value* LogosMethodCall::createIRValue(CodeGenMetadata* metadata) {
    vector<Value*> argValues;
    for (const auto& arg : args) {
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    const auto functionType = methodImpl->IRFunc->getFunctionType();
    const auto IRFunc = metadata->currentModule->getOrInsertFunction(methodImpl->combinedName, functionType);
    return metadata->builder.CreateCall(IRFunc, argValues);
}

string LogosMethodCall::getName() {
    return name;
}

LogosMethodCall::~LogosMethodCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
