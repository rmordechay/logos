#include "exprs/LogosVariableExpr.h"

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    const auto logosSymbol = metadata->theStack->getSymbol(name);
    const auto expr = logosSymbol->varDec->expr;
    return expr->getLLVMValue(metadata);
}
