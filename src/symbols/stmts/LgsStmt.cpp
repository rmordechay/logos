#include "stmts/LgsStmt.h"

#include "exprs/unary/LgsFuncCall.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include <loops/LgsLoop.h>

LgsAssignment* LgsStmt::asAssignment() {
    return dynamic_cast<LgsAssignment*>(this);
}

LgsLoop* LgsStmt::asLoop() {
    return dynamic_cast<LgsLoop*>(this);
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

LgsContinue* LgsStmt::asContinue() {
    return dynamic_cast<LgsContinue*>(this);
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
