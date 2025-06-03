#include "funcs/LgsMainFunc.h"
#include "types/LgsArray.h"

void LgsMainFunc::generateIRCode(LgsRuntime* runtime) {
    runtime->stack.enterFunc(this);
    startBlockFunc(runtime, nullptr);
    runtime->initRuntime(runtime);
    stmtBlock->createIRValue(runtime);
    runtime->freeExprs(runtime);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    runtime->stack.exitFunc();
}

Function* LgsMainFunc::getIRFunc(LgsRuntime* runtime) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    const auto hasParams = !funcType.params.empty();
    if (hasParams) {
        mainFuncType = FunctionType::get(i32Ty, {}, false);
    } else {
        mainFuncType = FunctionType::get(i32Ty, {i32Ty, ptrTy}, false);
    }
    const auto mainFuncIR = Function::Create(mainFuncType, Function::ExternalLinkage, LOGOS_MAIN_FUNC, runtime->module);
    IRFunc = mainFuncIR;
    if (hasParams) {
        auto args = mainFuncIR->arg_begin();
        args++->setName("argc");
        args->setName("argv");
    }
    return mainFuncIR;
}
