#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsFuncCall.h"
#include <LgsStack.h>
#include "stmts/LgsField.h"
#include <funcs/LgsFuncImpl.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case VAR_DEC:
        return symbol->varDec->IRValue;
    case PARAM:
        return symbol->param->IRValue;
    default:
        return nullptr;
    }
}
