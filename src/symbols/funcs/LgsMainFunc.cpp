#include "funcs/LgsMainFunc.h"

#include "exprs/unary/LgsArrayExpr.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsStr.h"

void LgsMainFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    if (!funcType.params.empty()) {
        const auto args = new LgsArrayExpr(new LgsStr());

        const auto func = getIRFunc(runtime);
    }
    startBlockFunc(runtime);
    runtime->initRuntime();
    stmtBlock->createIRValue(runtime);
    runtime->freeExprs();
    runtime->builder.CreateRet(runtime->builder.getInt32(EXIT_SUCCESS));
    runtime->stack.exitFunc();
}

Function* LgsMainFunc::getIRFunc(LgsRuntime* runtime) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    const auto arg = funcType.params.front();
    if (arg) {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {runtime->builder.getInt32Ty(), PointerType::getUnqual(context)}, false);
    } else {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {}, false);
    }
    auto func = runtime->module->getOrInsertFunction(LOGOS_MAIN_FUNC, mainFuncType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (arg) {
        auto IRArgs = IRFunc->arg_begin();
        argc = IRArgs;
        IRArgs->setName("argc");
        IRArgs++;
        argv = IRArgs;
        IRArgs->setName("argv");
    }
    return IRFunc;
}
