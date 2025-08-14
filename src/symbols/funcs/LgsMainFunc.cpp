#include "funcs/LgsMainFunc.h"
#include "exprs/unary/LgsArrayExpr.h"
#include <llvm/IR/Module.h>
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsStr.h"

void LgsMainFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(this, stmtsBlock);
    createPrologue(codeGen);
    if (!funcType->params.empty()) initMainArgs(codeGen);
    stmtsBlock->createIRValue(codeGen);
    createEpilogue(codeGen);
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
    IRFunc = codeGen->getFunc(LGS_MAIN_FUNC_NAME, mainFuncType);
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
    initArgsFunc = new LgsFunc("initArgs", &LGS_VOID);
    initArgsFunc->funcType->params.emplace_back(LgsParam(mainArgs->type));
    initArgsFunc->funcType->params.emplace_back(LgsParam(&LGS_INT));
    initArgsFunc->funcType->params.emplace_back(LgsParam(new LgsStr()));
}

void LgsMainFunc::initMainArgs(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    const std::vector<Type*> structFields{codeGen->i64Ty(), codeGen->i32Ty(), codeGen->i32Ty(), codeGen->ptrTy()};
    const auto arrStruct = codeGen->getStructType(structFields, LgsDArray::name);
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
