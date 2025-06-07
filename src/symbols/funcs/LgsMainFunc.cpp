#include "funcs/LgsMainFunc.h"

#include "builtin/LgsPrint.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"

void LgsMainFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    startBlockFunc(runtime);
    runtime->initRuntime();
    lgsPrint.call(runtime, {funcType.params.front()->expr});
    stmtBlock->createIRValue(runtime);
    runtime->freeExprs();
    runtime->builder.CreateRet(runtime->builder.getInt32(EXIT_SUCCESS));
    runtime->stack.exitFunc();
}

Function* LgsMainFunc::getIRFunc(LgsRuntime* runtime) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    const auto args = funcType.params.front();
    if (args) {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {}, false);
    } else {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {runtime->builder.getInt32Ty(), PointerType::getUnqual(context)}, false);
    }
    auto func = runtime->module->getOrInsertFunction(LOGOS_MAIN_FUNC, mainFuncType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (args) {
        auto IRArgs = IRFunc->arg_begin();
        IRArgs++->setName("argc");
        IRArgs->setName("argv");
    }
    // auto basicBlocks = Intrinsic::getDeclaration(runtime->module, Intrinsic::vastart);
    return IRFunc;
}
