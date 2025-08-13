#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsStr.h"

void LgsMainFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    startFuncBlock(codeGen);
    if (!funcType->params.empty()) {
        initMainArgs(codeGen);
    }
    stmtsBlock->createIRValue(codeGen);
    createEpilogueBlock(codeGen);
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
    auto func = codeGen->IRModule->getOrInsertFunction(LGS_MAIN_FUNC_NAME, mainFuncType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (funcType->params.empty()) return IRFunc;
    auto IRArgs = IRFunc->arg_begin();
    argc = IRArgs;
    IRArgs->setName("argc");
    argv = IRArgs++;
    IRArgs->setName("argv");
    return IRFunc;
}

void LgsMainFunc::setMainArgs() {
    mainArgs = new LgsArrayExpr(new LgsDArray(new LgsStr()));
    initArgsFunc = new LgsFunc("initArgs", &LGS_VOID, {LgsParam(mainArgs->type), LgsParam(&LGS_INT), LgsParam(new LgsStr())});
}

void LgsMainFunc::initMainArgs(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    const vector<Type*> structFields{codeGen->i64Ty(), codeGen->i32Ty(), codeGen->i32Ty(), codeGen->ptrTy()};
    const auto arrStruct = codeGen->getIRStructType(LgsDArray::name, structFields);
    mainArgs->IRValue = builder.CreateAlloca(arrStruct);
    initArgsFunc->callIR(codeGen, {mainArgs->IRValue, argc, argv});
    funcType->params[0].setIRValue(mainArgs->IRValue);
}

LgsMainFunc::~LgsMainFunc() {
    if (initArgsFunc) {
        delete initArgsFunc;
        initArgsFunc = nullptr;
    }
    if (mainArgs) {
        delete mainArgs;
        mainArgs = nullptr;
    }
}
