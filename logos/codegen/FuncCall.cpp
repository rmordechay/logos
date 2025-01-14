#include "FuncCall.h"

#include <exprs/LogosVariableExpr.h>

void FuncCall::generateProlog(RuntimeScope* scope) {
    Function* funcCall = scope->functions[funcCallExpr->func.name];
    auto formatStr = builder->CreateGlobalStringPtr("%d\n");
    if (funcCallExpr->args.size() == 0) {
        builder->CreateCall(funcCall);
        return;
    }
    const auto arg1 = funcCallExpr->args[0];
    if (const auto var = dynamic_cast<LogosVariableExpr*>(arg1)) {
        const auto symbol = scope->symbols[var->name];
        auto loadInst = builder->CreateLoad(symbol->getType(), symbol);
        builder->CreateCall(funcCall, {formatStr, loadInst});
        return;
    }
}

void FuncCall::generateEpilog(RuntimeScope* scope) {
}
