#include "LgsCoroutine.h"
#include "builtin/LgsBuiltins.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"
#include "utils/LgsIRUtils.h"

Value* callCoroIDFunc(LgsModule* module) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_id, {i32Ty(module)});
    return module->builder.CreateCall(func, {i32Zero(module), null(module), null(module), null(module)});
}

Value* callCoroSuspendFunc(LgsModule* module) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_suspend);
    return module->builder.CreateCall(func, {ConstantTokenNone::get(module->context), module->builder.getFalse()});
}

Value* callCoroSizeFunc(LgsModule* module) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_size, {i32Ty(module)});
    return module->builder.CreateCall(func);
}

Value* callCoroBeginFunc(LgsModule* module, Value* coroID, Value* frameSize) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_begin);
    const auto sizeValue = module->builder.CreateMalloc(i32Ty(module), i8Ty(module), frameSize, nullptr);
    return module->builder.CreateCall(func, {coroID, sizeValue});
}

Value* callCoroEndFunc(LgsModule* module, Value* handle) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_end, {i32Ty(module)});
    return module->builder.CreateCall(func, {handle, module->builder.getFalse(), ConstantTokenNone::get(module->context)});
}

Value* callCoroDestroyFunc(LgsModule* module, Value* handle) {
    const auto func = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_destroy, {i32Ty(module)});
    return module->builder.CreateCall(func, {handle});
}

void LgsCoroutine::createIRStmt(LgsModule* module) {
    auto& builder = module->builder;
    module->savedIP = builder.saveIP();

    vector<Type*> argTypes;
    vector<Value*> coroutineArgs;
    vector<Value*> originalArgs;
    const auto& args = funcCall ? funcCall->args : selection->lastExpr()->asFuncCall()->args;
    for (const auto arg : args) {
        originalArgs.push_back(arg->getIRValue(module));
        argTypes.push_back(arg->type->getIRType(module));
    }

    const auto ft = FunctionType::get(ptrTy(module), argTypes, false);
    const auto coroutineFunc = Function::Create(ft, GlobalValue::PrivateLinkage, "coroutine", module->IRModule);
    auto arg = coroutineFunc->arg_begin();
    for (int i = 0; i < args.size(); ++i) {
        coroutineArgs.push_back(arg++);
    }
    const auto entryBlock = BasicBlock::Create(module->context, BLOCK_NAME_ENTRY, coroutineFunc);
    const auto suspendBlock = BasicBlock::Create(module->context, BLOCK_NAME_SUSPEND, coroutineFunc);
    const auto resumeBlock = BasicBlock::Create(module->context, BLOCK_NAME_RESUME, coroutineFunc);
    const auto defaultBlock = BasicBlock::Create(module->context, BLOCK_NAME_DEFAULT_CASE, coroutineFunc);

    // Starts coroutine
    builder.SetInsertPoint(entryBlock);
    const auto coroID = callCoroIDFunc(module);
    const auto frameSize = callCoroSizeFunc(module);
    const auto handle = callCoroBeginFunc(module, coroID, frameSize);
    const auto suspend = callCoroSuspendFunc(module);
    const auto switchIR = builder.CreateSwitch(suspend, suspendBlock, 2);
    switchIR->addCase(i8(module, 0), resumeBlock);
    switchIR->addCase(i8(module, 1), defaultBlock);
    builder.SetInsertPoint(defaultBlock);
    builder.CreateRet(handle);
    builder.SetInsertPoint(suspendBlock);
    builder.CreateRet(handle);
    builder.SetInsertPoint(resumeBlock);

    if (stmtsBlock) {
        stmtsBlock->createIRValue(module);
    } else if (funcCall) {
        funcCall->func->callIR(module, coroutineArgs);
    } else if (selection) {
        selection->getIRValue(module);
    } else {
        assert(0);
    }
    callCoroEndFunc(module, handle);
    builder.CreateRet(handle);

    // Back to the caller
    builder.restoreIP(module->savedIP);
    const auto handler = builder.CreateCall(coroutineFunc, originalArgs);
    callCoroDestroyFunc(module, handler);
}
