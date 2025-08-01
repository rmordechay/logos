#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsStr.h"

void LgsMainFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    startFuncBlock(codeGen);
    codeGen->callInitRuntime();
    if (!funcType->params.empty()) {
        initArgs(codeGen);
    }
    stmtsBlock->createIRValue(codeGen);
    codeGen->builder.CreateRet(codeGen->i32(EXIT_SUCCESS));
    codeGen->stack.exitScope();
}

Function* LgsMainFunc::getIRFunc(LgsCodeGen* codeGen) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = FunctionType::get(codeGen->i32Ty(), {}, false);
    } else {
        mainFuncType = FunctionType::get(codeGen->i32Ty(), {codeGen->i32Ty(), codeGen->builder.getPtrTy()}, false);
    }
    auto func = codeGen->IRModule->getOrInsertFunction(LOGOS_MAIN_FUNC_NAME, mainFuncType);
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

void LgsMainFunc::initArgs(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    const vector<Type*> structFields{codeGen->i64Ty(), codeGen->i32Ty(), codeGen->i32Ty(), codeGen->ptrTy()};
    const auto arrStruct = codeGen->getIRStructType(args->type->asDArray()->name, structFields);
    args->IRValue = builder.CreateAlloca(arrStruct);
    initArgsFunc->callIR(codeGen, {args->IRValue, argc, argv});
    funcType->params[0].setIRValue(args->IRValue);
}

LgsMainFunc::~LgsMainFunc() {
    if (initArgsFunc) delete initArgsFunc;
    if (args) delete args;
}
