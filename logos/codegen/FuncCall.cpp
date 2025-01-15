#include "FuncCall.h"

#include <exprs/LogosVariableExpr.h>
#include <llvm/IR/Module.h>

void FuncCall::generateCode(RuntimeStackFrame* runtimeStack) {
    const auto funcSymbol = runtimeStack->functions[funcCallExpr->func.name];
    auto formatStr = builder->CreateGlobalStringPtr("%d\n");
    if (funcCallExpr->args.size() == 0) {
        builder->CreateCall(funcSymbol);
        return;
    }
    const auto arg1 = funcCallExpr->args[0];
    if (const auto var = dynamic_cast<LogosVariableExpr*>(arg1)) {
        const auto symbol = runtimeStack->symbolTable[var->name];
        auto loadInst = builder->CreateLoad(symbol->getType(), symbol);
        // builder->CreateCall(funcSymbol, {formatStr, loadInst});
        return;
    }
}
