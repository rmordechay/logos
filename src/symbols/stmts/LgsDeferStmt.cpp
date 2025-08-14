#include "stmts/LgsDeferStmt.h"
#include "funcs/LgsFunc.h"
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>

void LgsDeferStmt::createIRStmt(LgsCodeGen* codeGen) {
    const auto fc = funcCall ? funcCall : selection->lastExpr()->asFuncCall();
    Value* ctx = nullptr;
    if (!fc->args.empty()) {
        std::vector<Type*> types[fc->args.size()];
        for (int i = 0; i < fc->args.size(); i++) {
            types[i].emplace_back(fc->args[i]->type->getIRType(codeGen));
        }
        const auto ctxTy = codeGen->getStructType(*types);
        ctx = codeGen->builder.CreateAlloca(ctxTy);
        std::vector<Value*> values[fc->args.size()];
        for (int i = 0; i < fc->args.size(); i++) {
            const auto v = fc->args[i]->getIRValue(codeGen);
            codeGen->storeValueInStruct(ctxTy, ctx, i, v);
        }
    }
    const auto IRFunc = fc->func->getIRFunc(codeGen);
    codeGen->addDeferFunc(IRFunc, ctx);
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
