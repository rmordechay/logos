#include "LgsCoroutine.h"
#include "builtin/LgsBuiltins.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"
#include "utils/LgsIRUtils.h"

Value* callCoroIDFunc(LgsModule* module) {
    const auto coroIDFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_id);
    return module->builder.CreateCall(coroIDFunc, {i32Zero(module), null(module), null(module), null(module)});
}

Value* callCoroSizeFunc(LgsModule* module) {
    const auto coroSizeFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_size, {i32Ty(module)});
    return module->builder.CreateCall(coroSizeFunc);
}

Value* callCoroBeginFunc(LgsModule* module, Value* coroID, Value* frameSize) {
    const auto coroBeginFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_begin);
    const auto sizeValue = module->builder.CreateMalloc(i32Ty(module), i8Ty(module), frameSize, nullptr);
    return module->builder.CreateCall(coroBeginFunc, {coroID, sizeValue});
}

Value* callCoroDestroyFunc(LgsModule* module, Value* handle) {
    const auto coroDestroyFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_destroy);
    return module->builder.CreateCall(coroDestroyFunc, {handle});
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

    // Starts coroutine
    builder.SetInsertPoint(entryBlock);
    const auto coroID = callCoroIDFunc(module);
    const auto frameSize = callCoroSizeFunc(module);
    const auto handle = callCoroBeginFunc(module, coroID, frameSize);

    if (stmtsBlock) {
        stmtsBlock->createIRValue(module);
    } else if (funcCall) {
        funcCall->func->callIR(module, coroutineArgs);
    } else if (selection) {
        selection->getIRValue(module);
    } else {
        assert(0);
    }
    builder.CreateRet(handle);
    builder.restoreIP(module->savedIP);

    // Back to the caller
    const auto handler = builder.CreateCall(coroutineFunc, originalArgs);
    callCoroDestroyFunc(module, handler);
}
