#include "LogosVariableExpr.h"

#include "LogosConstant.h"
#include "LogosDefinitions.h"
#include "stmts/LogosVarDec.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::getLLVMValue(CodeGenMetadata* metadata) {
    const auto expr = metadata->theStack->getSymbol(name)->varDec->expr;
    return expr->getLLVMValue(metadata);
}
