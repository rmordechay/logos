#include "funcs/LgsMainFunc.h"

void LgsMainFunc::generateIRCode(Module* module) {
    setMainIR(module);
    runtime.enterFunc(this);
    startBlockFunc(module);
    runtime.initRuntime(module);
    runtime.push(module, location.getFullPath(path));
    stmtBlock->createIRValue(module);
    runtime.freeExprs(module);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    runtime.exitFunc();
}

void LgsMainFunc::setMainIR(Module* module) const {
    const auto mainFuncType = FunctionType::get(i32Ty, {i32Ty, ptrTy}, false);
    const auto mainFuncIR = Function::Create(mainFuncType, Function::ExternalLinkage, LOGOS_MAIN_FUNC, module);
    auto args = mainFuncIR->arg_begin();
    args++->setName("argc");
    args->setName("argv");
}