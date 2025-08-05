#include "LgsCoroutine.h"
#include "builtins/LgsBuiltins.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"

void LgsCoroutine::createIRStmt(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    codeGen->savedIP = builder.saveIP();
    const auto funcOrMethodCall = funcCall ? funcCall : selection->lastExpr()->asFuncCall();

    vector<Type*> argTypes;
    vector<Value*> coroutineArgs;
    vector<Value*> originalArgs;
    for (const auto arg : funcOrMethodCall->args) {
        originalArgs.push_back(arg->getIRValue(codeGen));
        argTypes.push_back(arg->type->getIRType(codeGen));
    }

    const auto ft = FunctionType::get(codeGen->ptrTy(), argTypes, false);
    const auto coroutineFunc = Function::Create(ft, GlobalValue::PrivateLinkage, "coroutine", codeGen->IRModule);
    auto arg = coroutineFunc->arg_begin();
    for (int i = 0; i < funcOrMethodCall->args.size(); ++i) {
        coroutineArgs.push_back(arg++);
    }
    const auto entryBlock = codeGen->createBlock(BLOCK_NAME_ENTRY, coroutineFunc);
    const auto suspendBlock = codeGen->createBlock(BLOCK_NAME_SUSPEND, coroutineFunc);
    const auto resumeBlock = codeGen->createBlock(BLOCK_NAME_RESUME, coroutineFunc);
    const auto defaultBlock = codeGen->createBlock(BLOCK_NAME_DEFAULT_CASE, coroutineFunc);

    // Starts coroutine
    builder.SetInsertPoint(entryBlock);
    const auto coroID = codeGen->callCoroIDFunc();
    const auto frameSize = codeGen->callCoroSizeFunc();
    const auto handle = codeGen->callBeginFunc(coroID, frameSize);
    const auto suspend = codeGen->callSuspendFunc();
    const auto switchIR = builder.CreateSwitch(suspend, suspendBlock, 2);
    switchIR->addCase(codeGen->i8(0), resumeBlock);
    switchIR->addCase(codeGen->i8(1), defaultBlock);
    builder.SetInsertPoint(defaultBlock);
    builder.CreateRet(handle);
    builder.SetInsertPoint(suspendBlock);
    builder.CreateRet(handle);
    builder.SetInsertPoint(resumeBlock);

    if (stmtsBlock) {
        stmtsBlock->createIRValue(codeGen);
    } else if (funcCall) {
        funcCall->func->callIR(codeGen, coroutineArgs);
    } else if (selection) {
        selection->getIRValue(codeGen);
    } else {
        assert(0);
    }
    codeGen->callCoroEndFunc(handle);
    builder.CreateRet(handle);

    // Back to the caller
    builder.restoreIP(codeGen->savedIP);
    const auto coroutine = builder.CreateCall(coroutineFunc, originalArgs);
    codeGen->callResumeFunc(coroutine);
    codeGen->callCoroDestroyFunc(coroutine);
}
