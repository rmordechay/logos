#include "FuncCall.h"

#include <exprs/LogosVariableExpr.h>
#include <llvm/IR/Module.h>

void FuncCall::generateCode(RuntimeStackFrame* runtimeStack) {
    const auto funcSymbol = runtimeStack->functions[funcCallExpr->func.name];
    Constant* formatStr = builder->CreateGlobalStringPtr("%d\n");
    const auto logosExprs = funcCallExpr->args;
    if (logosExprs.size() == 0) {
        builder->CreateCall(funcSymbol);
        return;
    }
    std::vector<Value*> args;
    args.push_back(formatStr);
    for (const auto logosExpr : logosExprs) {
        args.push_back(logosExpr->getLLVMValue(builder, runtimeStack));
    }
    builder->CreateCall(funcSymbol, ArrayRef(args));
}
