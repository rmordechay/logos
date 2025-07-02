#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsStr.h"
#include "utils/LgsUtils.h"

void LgsMainFunc::generateIR(LgsModule* module) {
    module->stack.enterFunc(this);
    module->IRFunc = getIRFunc(module);
    startFuncBlock(module);
    if (!funcType->params.empty()) {
        initArgs(module);
    }
    module->initRuntime();
    stmtBlock->createIRValue(module);
    module->IRFunc = nullptr;
    module->builder.CreateRet(module->builder.getInt32(EXIT_SUCCESS));
    module->stack.exitFunc();
}

Function* LgsMainFunc::getIRFunc(LgsModule* module) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = FunctionType::get(module->builder.getInt32Ty(), {}, false);
    } else {
        mainFuncType = FunctionType::get(module->builder.getInt32Ty(), {module->builder.getInt32Ty(), module->builder.getPtrTy()}, false);
    }
    auto func = module->IRModule->getOrInsertFunction(LOGOS_MAIN_FUNC, mainFuncType);
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

void LgsMainFunc::setArgs() {
    args = new LgsArrayExpr(new LgsStr());
    initArgsFunc = new LgsFunc("initArgs", &LGS_VOID, {LgsParam(args->type), LgsParam(&LGS_INT), LgsParam(new LgsStr())});
}

void LgsMainFunc::initArgs(LgsModule* runtime) {
    auto& builder = runtime->builder;
    const vector<Type*> structFields{builder.getInt64Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getPtrTy()};
    const auto arrStruct = getIRStructType(runtime->context, args->type->asArray()->name, structFields);
    args->IRValue = builder.CreateAlloca(arrStruct);
    initArgsFunc->callIR(runtime, {args->IRValue, argc, argv});
    funcType->params[0].setIRValue(args->IRValue);
}

LgsMainFunc::~LgsMainFunc() {
    if (initArgsFunc) delete initArgsFunc;
    if (args) delete args;
}
