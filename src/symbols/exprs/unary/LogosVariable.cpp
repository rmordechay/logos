#include "unary/LogosVariable.h"

#include "unary/LogosFuncCall.h"
#include "unary/LogosSelection.h"
#include "loops/LogosLoopVar.h"
#include "stmts/LogosField.h"

#include <LogosStack.h>
#include <binary/LogosBinaryExpr.h>
#include <funcs/LogosBuiltinFunc.h>
#include <funcs/LogosFuncImpl.h>

Value* LogosVariable::createIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case FIELD:
        return symbol->field->getIRValue(metadata);
    case SELECTION:
        return symbol->selection->getIRValue(metadata);
    case LOOP_VAR:
        return symbol->loopVar->getIRValue(metadata);
    case FUNC_IMPL:
        return symbol->funcImpl->getIRValue(metadata);
    case METHOD_IMPL:
        return symbol->methodImpl->getIRValue(metadata);
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

string LogosVariable::getName() {
    return name;
}