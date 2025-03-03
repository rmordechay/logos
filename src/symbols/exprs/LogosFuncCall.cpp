#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

#include <LogosStack.h>
#include <funcs/LogosBuiltinFunc.h>
#include <funcs/LogosFuncImpl.h>
#include <funcs/LogosMethodImpl.h>

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case BUILTIN_FUNC:
        return symbol->builtinFunc->callFunc(metadata, args);
    case FUNC_IMPL:
        return symbol->funcImpl->callFunc(metadata, args);
    case METHOD_IMPL:
        return symbol->methodImpl->callFunc(metadata, args);
    default:
        return nullptr;
    }
}

LogosSymbolType LogosFuncCall::getSymbolType() {
    return FUNC_CALL;
}

void LogosFuncCall::setName(const string name) {
    this->name = name;
}

string LogosFuncCall::getName() {
    return name;
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
