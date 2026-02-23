#include "stmts/LgsIfStmt.h"

#include <assert.h>

#include "exprs/LgsExpr.h"
#include "stmts/LgsStmtsBlock.h"

void LgsIfStmt::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsStmt* LgsIfStmt::clone() {
    const auto newLgsIfStmt = new LgsIfStmt(*this);
    newLgsIfStmt->ifCond = ifCond->clone();
    newLgsIfStmt->ifBlock = ifBlock->clone();
    if (elseBlock) newLgsIfStmt->elseBlock = elseBlock->clone();
    if (macroTrueBlock) newLgsIfStmt->macroTrueBlock = macroTrueBlock->clone();
    newLgsIfStmt->elseIfs.clear();
    for (const auto elseIf : elseIfs) {
        newLgsIfStmt->elseIfs.emplace_back(elseIf.first->clone(), elseIf.second->clone());
    }
    return newLgsIfStmt;
}

LgsIfStmt::~LgsIfStmt() {
    freeExpr(ifCond);
    ifCond = nullptr;
    if (ifBlock) {
        delete ifBlock;
        ifBlock = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : elseIfs) {
        freeExpr(expr);
        delete block;
    }
    elseIfs.clear();
}

