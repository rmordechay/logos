#include "stmts/LgsDeferStmt.h"
#include "configs/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>
#include <llvm/IR/Module.h>

void LgsDeferStmt::createIRValue(LgsCodeGen* codeGen) {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    const auto ctxTy = getCtxType(codeGen);
    Value* ctx;
    if (!fc->args.empty()) {
        ctx = codeGen->builder.CreateAlloca(ctxTy);
        for (int i = 0; i < fc->args.size(); i++) {
            Value* v = fc->args[i]->getIRValue(codeGen);
            codeGen->storeValueInStruct(dyn_cast<StructType>(ctxTy), ctx, i, v);
        }
    } else {
        ctx = codeGen->null();
    }
    const auto func = createThunkFunc(codeGen, ctxTy);
    codeGen->addDeferFunc(func, ctx);
}

Function* LgsDeferStmt::createThunkFunc(LgsCodeGen* codeGen, Type* ctxTy) const {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    const auto deferFunc = fc->func->getIRFunc(codeGen);
    auto func = codeGen->IRModule->getFunction(fc->name + "_thunk");
    if (func) return func;

    codeGen->savedIP = codeGen->builder.saveIP();
    const auto ft = FunctionType::get(codeGen->voidTy(), {codeGen->ptrTy()}, false);
    func = Function::Create(ft, Function::PrivateLinkage, fc->name + "_thunk", codeGen->IRModule);
    const auto entryBlock = BasicBlock::Create(codeGen->context, BLOCK_NAME_ENTRY);
    entryBlock->insertInto(func);
    codeGen->builder.SetInsertPoint(entryBlock);

    std::vector<Value*> args;
    for (int i = 0; i < fc->args.size(); i++) {
        const auto fieldTy = dyn_cast<StructType>(ctxTy)->getElementType(i);
        const auto fieldPtr = codeGen->builder.CreateStructGEP(ctxTy, func->arg_begin(), i);
        const auto v = codeGen->builder.CreateLoad(fieldTy, fieldPtr);
        args.push_back(v);
    }
    codeGen->builder.CreateCall(deferFunc, args);
    codeGen->builder.CreateRetVoid();

    codeGen->builder.restoreIP(codeGen->savedIP);
    return func;
}

Type* LgsDeferStmt::getCtxType(LgsCodeGen* codeGen) const {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    if (fc->args.empty()) return codeGen->ptrTy();
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg->type->getIRType(codeGen));
    }
    return codeGen->getStructType(types, fc->name + "_thunk_type");
}

void LgsDeferStmt::generateIR(LgsCodeGen* codeGen) const {
    if (funcCall) {
        funcCall->createIRValue(codeGen);
    } else if (selection) {
        selection->createIRValue(codeGen);
    }
}

LgsDeferStmt::~LgsDeferStmt() {
    if (funcCall) {
        delete funcCall;
        funcCall = nullptr;
    }
    if (selection) {
        delete selection;
        selection = nullptr;
    }
}
