#include "unary/LgsFuncCall.h"

#include <LgsStack.h>
#include "funcs/LgsFunc.h"

string LgsFuncCall::getName() {
    return name;
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(composedName);
    if (symbol->type != FUNC_IMPL) return nullptr;
    return symbol->func->call(metadata, args);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
