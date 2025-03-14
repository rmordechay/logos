#include "unary/LgsFuncCall.h"

#include <LgsStack.h>
#include "funcs/LgsFunc.h"
#include "funcs/LgsFuncImpl.h"

#include <funcs/LgsBuiltinFunc.h>

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    if (symbol->type == BUILTIN_FUNC) {
        return symbol->builtinFunc->call(metadata, args);
    }
    if (symbol->type == FUNC_IMPL) {
        return symbol->funcImpl->call(metadata, args);
    }
    return nullptr;
}

string LgsFuncCall::getName() {
    return name;
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
