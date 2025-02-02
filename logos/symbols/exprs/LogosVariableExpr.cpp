#include "LogosVariableExpr.h"

#include "LogosConstant.h"
#include "LogosDefinitions.h"
#include "stmts/LogosVarDec.h"

#include <llvm/IR/Module.h>

Value* LogosVariable::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto expr = theStack->getSymbol(name)->varDec->expr;
    return expr->getLLVMValue(builder, theStack, module);
}
