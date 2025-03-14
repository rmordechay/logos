#include "unary/LgsVariable.h"

#include "unary/LgsFuncCall.h"
#include "unary/LgsSelection.h"
#include "stmts/LgsField.h"

#include <LgsStack.h>
#include <binary/LgsBinaryExpr.h>
#include <funcs/LgsBuiltinFunc.h>
#include <funcs/LgsFuncImpl.h>

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case SELECTION:
        return symbol->selection->getIRValue(metadata);
    case FUNC_IMPL:
        return symbol->funcImpl->getIRValue(metadata);
    case VAR_DEC:
        return symbol->varDec->getIRValue(metadata);
    case BUILTIN_FUNC:
        return symbol->builtinFunc->getIRValue(metadata);
    case PARAM:
        return symbol->param->getIRValue(metadata);
    default:
        return nullptr;
    }
}

string LgsVariable::getName() {
    return name;
}