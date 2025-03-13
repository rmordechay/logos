#include "unary/LogosFuncCall.h"

#include <LogosStack.h>
#include "funcs/LogosFunc.h"
#include "funcs/LogosFuncImpl.h"

#include <funcs/LogosBuiltinFunc.h>

Value* LogosFuncCall::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    if (symbol->type == BUILTIN_FUNC) {
        return symbol->builtinFunc->call(metadata, args);
    }
    if (symbol->type == FUNC_IMPL) {
        return symbol->funcImpl->call(metadata, args);
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
