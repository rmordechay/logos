#include "exprs/LogosFuncCall.h"

#include "funcs/LogosFunc.h"

LogosSymbolType LogosFuncCall::getSymbolType() {
    return FUNC_CALL;
}

string LogosFuncCall::getName() {
    return name;
}

Value* LogosFuncCall::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->theStack->getSymbol(name);
    return symbol->func->callFunc(metadata, args);
}

LogosFuncCall::~LogosFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
