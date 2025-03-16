#include "unary/LgsVariable.h"

#include "unary/LgsFuncCall.h"
#include "stmts/LgsField.h"

#include <LgsStack.h>
#include <binary/LgsBinaryExpr.h>
#include <funcs/LgsFuncImpl.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->getIRValue(metadata);
    case FUNC:
        return symbol->func->getIRValue(metadata);
    case PARAM:
        return symbol->param->getIRValue(metadata);
    default:
        return nullptr;
    }
}
