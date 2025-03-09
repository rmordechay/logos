#include "exprs/LogosFuncCall.h"

#include <LogosStack.h>
#include "funcs/LogosFunc.h"
#include <funcs/LogosBuiltinFunc.h>
#include <funcs/LogosFuncImpl.h>
#include <funcs/LogosMethodImpl.h>

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    if (symbol->type == BUILTIN_FUNC) return symbol->builtinFunc->call(metadata, args);
    if (symbol->type == FUNC_IMPL) return symbol->funcImpl->call(metadata, args);
    if (symbol->type == METHOD_IMPL) return symbol->methodImpl->call(metadata, args);
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
