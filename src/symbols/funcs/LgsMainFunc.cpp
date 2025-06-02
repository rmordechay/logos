#include "funcs/LgsMainFunc.h"

#include "types/LgsArray.h"

void LgsMainFunc::generateIRCode(Module* module) {
    runtime.enterFunc(this);
    startBlockFunc(module);
    runtime.initRuntime(module);
    stmtBlock->createIRValue(module);
    runtime.freeExprs(module);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    runtime.exitFunc();
}

Function* LgsMainFunc::getIRFunc(Module* module) {
    if (IRFunc) return IRFunc;
    if (funcType.params.empty()) {
        const auto mainFuncType = FunctionType::get(i32Ty, {}, false);
        return Function::Create(mainFuncType, Function::ExternalLinkage, LOGOS_MAIN_FUNC, module);
    }
    const auto mainFuncType = FunctionType::get(i32Ty, {i32Ty, ptrTy}, false);
    const auto mainFuncIR = Function::Create(mainFuncType, Function::ExternalLinkage, LOGOS_MAIN_FUNC, module);
    auto args = mainFuncIR->arg_begin();
    args++->setName("argc");
    args->setName("argv");
    IRFunc = mainFuncIR;
    return mainFuncIR;
}
