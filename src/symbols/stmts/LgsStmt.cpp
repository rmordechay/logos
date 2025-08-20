#include "stmts/LgsStmt.h"
#include "../../../include/symbols/funcs/LgsCoroutine.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsSelection.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsDeferStmt.h"

bool LgsStmt::isTerminator() {
    const bool isControlFlow = dynamic_cast<LgsBreak*>(this) || dynamic_cast<LgsContinue*>(this) || dynamic_cast<LgsReturn*>(this);
    if (isControlFlow) return true;
    const auto fc = asFuncCall();
    if (fc && fc->func && fc->func->funcType->isTerminator) return true;
    const auto selection = asSelection();
    if (!selection) return false;
    const auto methodCall = selection->lastExpr()->asFuncCall();
    if (!methodCall) return false;
    return methodCall->func && methodCall->func->funcType->isTerminator;
}

LgsForLoop* LgsStmt::asLoop() { return dynamic_cast<LgsForLoop*>(this); }
LgsCoroutine* LgsStmt::asCoroutine() { return dynamic_cast<LgsCoroutine*>(this); }
LgsDeferStmt* LgsStmt::asDefer() { return dynamic_cast<LgsDeferStmt*>(this); }
LgsFuncCall* LgsStmt::asFuncCall() { return dynamic_cast<LgsFuncCall*>(this); }
LgsIfStmt* LgsStmt::asIfStmt() { return dynamic_cast<LgsIfStmt*>(this); }
LgsPostfixExpr* LgsStmt::asPostfixExpr() { return dynamic_cast<LgsPostfixExpr*>(this); }
LgsSelection* LgsStmt::asSelection() { return dynamic_cast<LgsSelection*>(this); }
LgsBreak* LgsStmt::asBreak() { return dynamic_cast<LgsBreak*>(this); }
LgsContinue* LgsStmt::asContinue() { return dynamic_cast<LgsContinue*>(this); }
LgsReturn* LgsStmt::asReturn() { return dynamic_cast<LgsReturn*>(this); }
LgsVarDec* LgsStmt::asVarDec() { return dynamic_cast<LgsVarDec*>(this); }
LgsAssignment* LgsStmt::asAssignment() { return dynamic_cast<LgsAssignment*>(this); }
