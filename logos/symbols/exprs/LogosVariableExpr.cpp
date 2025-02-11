#include "LogosVariableExpr.h"

#include "LogosConstant.h"
#include "LogosDefinitions.h"
#include "stmts/LogosVarDec.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    auto logosSymbol = metadata->theStack->getSymbol(name);
    const auto expr = logosSymbol->varDec->expr;
    return expr->getLLVMValue(metadata);
}
