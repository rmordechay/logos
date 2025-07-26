#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsSingleton.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "utils/LgsIRUtils.h"

void LgsMainFunc::generateIR(LgsModule* module) {
    module->stack.enterScope(FUNC_SCOPE, this);
    startFuncBlock(module);
    if (!funcType->params.empty()) initArgs(module);
    for (auto [_, symbol] : module->globals.symbols) {
        if (symbol.symbolType != OBJECT) continue;
        const auto obj = symbol.object;
        if (obj->singleton) {
            obj->singleton->createIRValue(module);
        }
    }
    stmtBlock->createIRValue(module);
    module->builder.CreateRet(i32(module, EXIT_SUCCESS));
    module->stack.exitScope();
}

Function* LgsMainFunc::getIRFunc(LgsModule* module) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = FunctionType::get(i32Ty(module), {}, false);
    } else {
        mainFuncType = FunctionType::get(i32Ty(module), {i32Ty(module), module->builder.getPtrTy()}, false);
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
    args = new LgsArrayExpr(new LgsDArray(new LgsStr()));
    initArgsFunc = new LgsFunc("initArgs", &LGS_VOID, {LgsParam(args->type), LgsParam(&LGS_INT), LgsParam(new LgsStr())});
}

void LgsMainFunc::initArgs(LgsModule* module) {
    auto& builder = module->builder;
    const vector<Type*> structFields{i64Ty(module), i32Ty(module), i32Ty(module), ptrTy(module)};
    const auto arrStruct = getIRStructType(module->context, args->type->asDArray()->name, structFields);
    args->IRValue = builder.CreateAlloca(arrStruct);
    initArgsFunc->callIR(module, {args->IRValue, argc, argv});
    funcType->params[0].setIRValue(args->IRValue);
}

LgsMainFunc::~LgsMainFunc() {
    if (initArgsFunc) delete initArgsFunc;
    if (args) delete args;
}
