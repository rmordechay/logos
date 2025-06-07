#include "funcs/LgsMainFunc.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"

void LgsMainFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
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
    const auto hasParams = !funcType.params.empty();
    if (hasParams) {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {runtime->builder.getInt32Ty(), PointerType::getUnqual(context)}, false);
    } else {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {}, false);
    }
    auto func = runtime->module->getOrInsertFunction(LOGOS_MAIN_FUNC, mainFuncType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (hasParams) {
        auto args = IRFunc->arg_begin();
        args++->setName("argc");
        args->setName("argv");
    }
    return IRFunc;
}
