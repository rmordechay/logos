#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsStmtBlock.h"
#include "utils/LgsUtils.h"

void LgsMainFunc::generateIR(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    startBlockFunc(runtime);
    if (!funcType->params.empty()) {
        initArgs(runtime);
    }
    runtime->initRuntime();
    stmtBlock->createIRValue(runtime);
    runtime->freeExprs();
    runtime->builder.CreateRet(runtime->builder.getInt32(EXIT_SUCCESS));
    runtime->stack.exitFunc();
}

Function* LgsMainFunc::getIRFunc(LgsRuntime* runtime) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {}, false);
    } else {
        mainFuncType = FunctionType::get(runtime->builder.getInt32Ty(), {runtime->builder.getInt32Ty(), runtime->builder.getPtrTy()}, false);
    }
    auto func = runtime->module->getOrInsertFunction(LOGOS_MAIN_FUNC, mainFuncType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (funcType->params.empty()) return IRFunc;
    auto IRArgs = IRFunc->arg_begin();
    argc = IRArgs;
    IRArgs->setName("argc");
    IRArgs++;
    argv = IRArgs;
    IRArgs->setName("argv");
    return IRFunc;
}

void LgsMainFunc::initArgs(LgsRuntime* runtime) {
    auto& builder = runtime->builder;
    const vector<Type*> structFields{builder.getInt64Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getPtrTy()};
    const auto arrStruct = getIRStructType(args->type->asArray()->name, structFields);
    args->IRValue = builder.CreateAlloca(arrStruct);
    initArgsFunc->callIR(runtime, {args->IRValue, argc, argv});
    funcType->params[0].setIRValue(args->IRValue);
}
