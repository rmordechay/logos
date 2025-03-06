#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

#include <LogosStack.h>
#include <funcs/LogosBuiltinFunc.h>
#include <funcs/LogosFuncImpl.h>
#include <funcs/LogosMethodImpl.h>

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    if (symbol->type == BUILTIN_FUNC) return symbol->builtinFunc->callFunc(metadata, args);
    if (symbol->type == FUNC_IMPL) return symbol->funcImpl->callFunc(metadata, args);
    if (symbol->type == METHOD_IMPL) return symbol->methodImpl->callFunc(metadata, args);
    return nullptr;
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
