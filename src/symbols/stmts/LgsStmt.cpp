#include "stmts/LgsStmt.h"

#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include <loops/LgsForLoop.h>

LgsAssignment* LgsStmt::asAssignment() {
    return dynamic_cast<LgsAssignment*>(this);
}

LgsForLoop* LgsStmt::asLoop() {
    return dynamic_cast<LgsForLoop*>(this);
}

LgsBreakStmt* LgsStmt::asBreakStmt() {
    return dynamic_cast<LgsBreakStmt*>(this);
}

LgsFuncCall* LgsStmt::asFuncCall() {
    return dynamic_cast<LgsFuncCall*>(this);
}

LgsSelection* LgsStmt::asSelection() {
    return dynamic_cast<LgsSelection*>(this);
}

LgsPostfixExpr* LgsStmt::asPostfixExpr() {
    return dynamic_cast<LgsPostfixExpr*>(this);
}

LgsContinueStmt* LgsStmt::asContinue() {
    return dynamic_cast<LgsContinueStmt*>(this);
}

LgsIfStmt* LgsStmt::asIfStmt() {
    return dynamic_cast<LgsIfStmt*>(this);
}

LgsPatternMatch* LgsStmt::asPatternMatch() {
    return dynamic_cast<LgsPatternMatch*>(this);
}

LgsReturn* LgsStmt::asReturn() {
    return dynamic_cast<LgsReturn*>(this);
}

LgsVarDec* LgsStmt::asVarDec() {
    return dynamic_cast<LgsVarDec*>(this);
}
