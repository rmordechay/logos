#include "stmts/LgsStmtsBlock.h"

#include <assert.h>
#include <string>

#include "stmts/LgsReturn.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "types/LgsObject.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "stmts/LgsStmt.h"
#include "types/LgsFuncType.h"

bool LgsStmtWrapper::isTerminator() const {
    switch (wrapperType) {
    case WrapperType::Stmt: {
        const bool isControlFlow = dynamic_cast<LgsBreak*>(stmt) || dynamic_cast<LgsContinue*>(stmt) || dynamic_cast<LgsReturn*>(stmt);
        if (isControlFlow) return true;
        break;
    }
    case WrapperType::Expr: {
        const auto fc = expr->asFuncCall();
        if (fc && fc->func && fc->func->funcType->isTerminator) return true;
        const auto selection = expr->asSelection();
        if (!selection) break;
        const auto methodCall = selection->asMethodCall();
        if (!methodCall) break;
        return methodCall->func && methodCall->func->funcType->isTerminator;
    }
    case WrapperType::Object:
        break;
    }
    return false;
}

LgsFunc* LgsStmtsBlock::wrapBlockInFunc() {
    const auto func = new LgsFunc("", nullptr);
    func->isLambda = true;
    func->location = location;
    func->stmtsBlock = this;
    return func;
}

void LgsStmtsBlock::hashNode(size_t& oldHash) {
    for (const auto stmt : stmts) {
        stmt.stmt->hashNode(oldHash);
    }
}

void LgsStmtsBlock::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsStmtsBlock* LgsStmtsBlock::clone() const {
    const auto newStmtBlock = new LgsStmtsBlock();
    for (const auto& stmtWrapper : stmts) {
        switch (stmtWrapper.wrapperType) {
        case LgsStmtWrapper::WrapperType::Stmt: {
            LgsStmtWrapper stmt((stmtWrapper.stmt->clone()));
            newStmtBlock->stmts.push_back(stmt);
            break;
        }
        case LgsStmtWrapper::WrapperType::Expr: {
            LgsStmtWrapper expr((stmtWrapper.expr->clone()));
            newStmtBlock->stmts.push_back(expr);
            break;
        }
        case LgsStmtWrapper::WrapperType::Object:
            assert(0);
        }
    }
    return newStmtBlock;
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Stmt:
            freeStmt(stmt.stmt);
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            freeExpr(stmt.expr);
            break;
        case LgsStmtWrapper::WrapperType::Object:
            freeType(stmt.obj);
            break;
        }
    }
    stmts.clear();
}
