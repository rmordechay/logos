#include "unary/LogosMethodCall.h"
#include "funcs/LogosMethodImpl.h"

Value* LogosMethodCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    return symbol->methodImpl->call(metadata, args);
}

string LogosMethodCall::getName() {
    return name;
}

LogosMethodCall::~LogosMethodCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
