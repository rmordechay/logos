#include "stmts/LgsStmt.h"
#include "LgsCoroutine.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsSelection.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include "loops/LgsForLoop.h"

bool LgsStmt::isTerminator() {
    return asReturn() || asContinue() || asBreak();
}

LgsForLoop* LgsStmt::asLoop() { return dynamic_cast<LgsForLoop*>(this); }
LgsCoroutine* LgsStmt::asCoroutine() { return dynamic_cast<LgsCoroutine*>(this); }
LgsFuncCall* LgsStmt::asFuncCall() { return dynamic_cast<LgsFuncCall*>(this); }
LgsIfStmt* LgsStmt::asIfStmt() { return dynamic_cast<LgsIfStmt*>(this); }
LgsPostfixExpr* LgsStmt::asPostfixExpr() { return dynamic_cast<LgsPostfixExpr*>(this); }
LgsSelection* LgsStmt::asSelection() { return dynamic_cast<LgsSelection*>(this); }
LgsBreakStmt* LgsStmt::asBreak() { return dynamic_cast<LgsBreakStmt*>(this); }
LgsContinueStmt* LgsStmt::asContinue() { return dynamic_cast<LgsContinueStmt*>(this); }
LgsReturn* LgsStmt::asReturn() { return dynamic_cast<LgsReturn*>(this); }
LgsVarDec* LgsStmt::asVarDec() { return dynamic_cast<LgsVarDec*>(this); }
LgsAssignment* LgsStmt::asAssignment() { return dynamic_cast<LgsAssignment*>(this); }
