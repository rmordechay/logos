#include "unary/LogosMethodCall.h"

#include "LogosInstance.h"
#include "funcs/LogosMethodImpl.h"

Value* LogosMethodCall::createIRValue(CodeGenMetadata* metadata) {
    return methodImpl->call(metadata, args);
}

string LogosMethodCall::getName() {
    return name;
}

LogosMethodCall::~LogosMethodCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
