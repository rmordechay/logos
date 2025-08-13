#include "stmts/LgsDeferStmt.h"
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsSelection.h>
#include <stmts/LgsStmtsBlock.h>

void LgsDeferStmt::createIRStmt(LgsCodeGen* codeGen) {
    if (funcCall) {
        for (const auto& arg : funcCall->args) {
            arg->getIRValue(codeGen);
        }
    } else if (selection) {
        const auto methodCall = selection->lastExpr()->asFuncCall();
        for (const auto& arg : methodCall->args) {
            arg->getIRValue(codeGen);
        }
    }
}

void LgsDeferStmt::generateIR(LgsCodeGen* codeGen) const {
    if (stmtsBlock) {
        stmtsBlock->createIRValue(codeGen);
    } else if (funcCall) {
        funcCall->createIRValue(codeGen);
    } else if (selection) {
        selection->createIRValue(codeGen);
    }
}

LgsDeferStmt::~LgsDeferStmt() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    if (funcCall) {
        delete funcCall;
        funcCall = nullptr;
    }
    if (selection) {
        delete selection;
        selection = nullptr;
    }
}
