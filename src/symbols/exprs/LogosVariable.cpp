#include "exprs/LogosVariable.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "loops/LogosLoopVar.h"
#include "object/LogosField.h"

#include <LogosStack.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosBinaryExpr.h>
#include <exprs/LogosConstant.h>
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
    default:
        return nullptr;
    }
}

void LogosVariable::setName(const string name) {
    this->name = name;
}

string LogosVariable::getName() {
    return name;
}