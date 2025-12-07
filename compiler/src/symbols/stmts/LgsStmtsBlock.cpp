#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "types/LgsObject.h"

bool LgsStmtWrapper::isTerminator() const {
    switch (type) {
    case Type::Stmt: {
        const bool isControlFlow = dynamic_cast<LgsBreak*>(stmt) || dynamic_cast<LgsContinue*>(stmt) || dynamic_cast<LgsReturn*>(stmt);
        if (isControlFlow) return true;
        break;
    }
    case Type::Expr: {
        const auto fc = expr->asFuncCall();
        if (fc && fc->func && fc->func->funcType->isTerminator) return true;
        const auto selection = expr->asSelection();
        if (!selection) break;
        const auto methodCall = selection->asMethodCall();
        if (!methodCall) break;
        return methodCall->func && methodCall->func->funcType->isTerminator;
    }
    case Type::Object:
        break;
    }
    return false;
}

LgsStmtWrapper LgsStmtWrapper::clone() const {
    switch (type) {
    case Type::Stmt:
        return LgsStmtWrapper(stmt->clone());
    case Type::Expr:
        return LgsStmtWrapper(expr->clone());
    case Type::Object:
        assert(0);
    }
    return LgsStmtWrapper();
}

void LgsStmtsBlock::hashNode(size_t& oldHash) {
    for (const auto stmt : stmts) {
        stmt.stmt->hashNode(oldHash);
    }
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        switch (stmt.type) {
        case LgsStmtWrapper::Type::Stmt:
            freeStmt(stmt.stmt);
            break;
        case LgsStmtWrapper::Type::Expr:
            freeExpr(stmt.expr);
            break;
        case LgsStmtWrapper::Type::Object:
            freeType(stmt.obj);
            break;
        }
    }
    stmts.clear();
}

void LgsStmtsBlock::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

LgsStmtsBlock* LgsStmtsBlock::clone() const {
    const auto newBlock = new LgsStmtsBlock();
    for (const auto& stmt : stmts) {
        newBlock->stmts.push_back(stmt.clone());
    }
    return newBlock;
}
