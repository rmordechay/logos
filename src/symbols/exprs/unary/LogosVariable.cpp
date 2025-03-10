#include "unary/LogosVariable.h"

#include "unary/LogosFuncCall.h"
#include "unary/LogosSelection.h"
#include "loops/LogosLoopVar.h"
#include "object/LogosField.h"

#include <LogosStack.h>
#include <binary/LogosBinaryExpr.h>
#include <funcs/LogosBuiltinFunc.h>
#include <funcs/LogosFuncImpl.h>

Value* LogosVariable::computeIRValue(CodeGenMetadata* metadata) {
    const auto symbol = metadata->logosStack.getSymbol(name);
    switch (symbol->type) {
    case FIELD:
        return symbol->field->writeIRValue(metadata);
    case SELECTION:
        return symbol->selection->writeIRValue(metadata);
    case LOOP_VAR:
        return symbol->loopVar->writeIRValue(metadata);
    case FUNC_IMPL:
        return symbol->funcImpl->writeIRValue(metadata);
    case METHOD_IMPL:
        return symbol->methodImpl->writeIRValue(metadata);
    case VAR_DEC:
        return symbol->varDec->writeIRValue(metadata);
    case BUILTIN_FUNC:
        return symbol->builtinFunc->writeIRValue(metadata);
    case PARAM:
        return symbol->param->writeIRValue(metadata);
    default:
        return nullptr;
    }
}

string LogosVariable::getName() {
    return name;
}