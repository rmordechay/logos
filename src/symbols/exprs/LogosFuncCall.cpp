#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

#include <LogosStack.h>
#include <funcs/LogosFuncImpl.h>

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    return symbol->funcImpl->callFunc(metadata, args);
}

LogosSymbolType LogosFuncCall::getSymbolType() {
    return FUNC_CALL;
}

string LogosFuncCall::getName() {
    return name;
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
